param(
    [Parameter(Position = 0)]
    [string]$File,

    [Parameter(Position = 1)]
    [string]$ProcessingDir
)

$ErrorActionPreference = 'Stop'

$defaultFiles = @(
    'generate/include/cxx_include/esp_modem_command_library.hpp',
    'generate/include/cxx_include/esp_modem_dce_module.hpp',
    'generate/include/cxx_include/esp_modem_dce_generic.hpp',
    'generate/src/esp_modem_modules.cpp',
    'generate/include/esp_modem_api.h'
)

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$defaultProcessingDir = [System.IO.Path]::GetFullPath((Join-Path $scriptDir '..'))
$startMarker = 'ESP-MODEM command module starts here'
$endMarker = 'ESP-MODEM command module ends here'
$utf8NoBom = New-Object System.Text.UTF8Encoding($false)

if ([string]::IsNullOrWhiteSpace($File)) {
    $files = $defaultFiles
} else {
    $files = @($File)
}

if ([string]::IsNullOrWhiteSpace($ProcessingDir)) {
    $processingRoot = $defaultProcessingDir
} else {
    $processingRoot = [System.IO.Path]::GetFullPath($ProcessingDir)
}

foreach ($relativeFile in $files) {
    $inputFile = [System.IO.Path]::GetFullPath((Join-Path $processingRoot $relativeFile))
    $outputRelative = [System.Text.RegularExpressions.Regex]::Replace($relativeFile, 'generate', 'command', 1)
    $outputFile = [System.IO.Path]::GetFullPath((Join-Path $processingRoot $outputRelative))
    $currentFileDir = Split-Path -Parent $inputFile

    if (-not (Test-Path -LiteralPath $inputFile -PathType Leaf)) {
        throw "Input file not found: $inputFile"
    }

    $outputDir = Split-Path -Parent $outputFile
    if (-not (Test-Path -LiteralPath $outputDir -PathType Container)) {
        New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
    }

    Write-Host "Processing $inputFile"

    $lines = Get-Content -LiteralPath $inputFile

    $startIndex = -1
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -like "*$startMarker*") {
            $startIndex = $i
            break
        }
    }

    $endIndex = -1
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -like "*$endMarker*") {
            $endIndex = $i
            break
        }
    }

    if ($startIndex -eq -1) {
        $headerLines = $lines
        $bodyLines = @()
    } else {
        if ($startIndex -gt 0) {
            $headerLines = $lines[0..($startIndex - 1)]
        } else {
            $headerLines = @()
        }

        if ($startIndex -lt ($lines.Count - 1)) {
            $bodyLines = $lines[($startIndex + 1)..($lines.Count - 1)]
        } else {
            $bodyLines = @()
        }
    }

    if ($endIndex -ne -1 -and $endIndex -lt ($lines.Count - 1)) {
        $footerLines = $lines[($endIndex + 1)..($lines.Count - 1)]
    } else {
        $footerLines = @()
    }

    [System.IO.File]::WriteAllText($outputFile, (($headerLines -join "`n") + "`n"), $utf8NoBom)

    if ($relativeFile -match '\.(cpp|hpp)$') {
        $compilerExe = 'clang++'
        $compilerArgs = @('-E', '-P', '-CC', '-xc++')
    } elseif ($relativeFile -match '\.rst$') {
        $compilerExe = 'clang'
        $compilerArgs = @('-E', '-P', '-xc')
    } else {
        $compilerExe = 'clang'
        $compilerArgs = @('-E', '-P', '-CC', '-xc')
    }

    if (-not (Get-Command $compilerExe -ErrorAction SilentlyContinue)) {
        throw "Required compiler not found in PATH: $compilerExe"
    }

    $includeArgs = @(
        "-I$scriptDir",
        "-I$processingRoot/generate/include",
        "-I$processingRoot/include",
        "-I$currentFileDir"
    )

    $tempBodyFile = [System.IO.Path]::GetTempFileName()
    try {
        [System.IO.File]::WriteAllText($tempBodyFile, ($bodyLines -join "`n"), $utf8NoBom)
        $preprocessed = & $compilerExe @compilerArgs @includeArgs $tempBodyFile
        if ($LASTEXITCODE -ne 0) {
            throw "Preprocessor failed for $inputFile"
        }
    } finally {
        Remove-Item -LiteralPath $tempBodyFile -ErrorAction SilentlyContinue
    }

    if ($preprocessed) {
        [System.IO.File]::AppendAllText($outputFile, (($preprocessed -join "`n") + "`n"), $utf8NoBom)
    }

    if ($footerLines.Count -gt 0) {
        [System.IO.File]::AppendAllText($outputFile, (($footerLines -join "`n") + "`n"), $utf8NoBom)
    }

    if ($outputFile -notmatch '\.rst$') {
        if (-not (Get-Command 'astyle' -ErrorAction SilentlyContinue)) {
            throw 'Required formatter not found in PATH: astyle'
        }

        & astyle --style=otbs --attach-namespaces --attach-classes --indent=spaces=4 --convert-tabs --align-pointer=name --align-reference=name --keep-one-line-statements --pad-header --pad-oper --unpad-paren --quiet --max-continuation-indent=120 $outputFile
        if ($LASTEXITCODE -ne 0) {
            throw "astyle failed for $outputFile"
        }
    }
}

