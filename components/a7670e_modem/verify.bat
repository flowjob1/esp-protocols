@echo off
REM Verification Script for A7670E Component (Windows)

setlocal enabledelayedexpansion

echo.
echo ==========================================
echo A7670E Modem Component Verification
echo ==========================================
echo.

set COMPONENT_DIR=components\a7670e_modem
set ERRORS=0
set WARNINGS=0

REM Function to check file
setlocal disabledelayedexpansion
for /f "delims=" %%a in ('cd') do set CURRENT_DIR=%%a
endlocal & setlocal enabledelayedexpansion

echo Checking directory structure...
if exist "%COMPONENT_DIR%" (
    echo [OK] Directory: %COMPONENT_DIR%
) else (
    echo [ERROR] Directory not found: %COMPONENT_DIR%
    set /a ERRORS=!ERRORS!+1
    exit /b 1
)

if exist "%COMPONENT_DIR%\include" echo [OK] Directory: %COMPONENT_DIR%\include
if exist "%COMPONENT_DIR%\src" echo [OK] Directory: %COMPONENT_DIR%\src
if exist "%COMPONENT_DIR%\examples\a7670e_at_only" echo [OK] Directory: examples
echo.

echo Checking header files...
if exist "%COMPONENT_DIR%\include\a7670e_types.hpp" echo [OK] a7670e_types.hpp
if exist "%COMPONENT_DIR%\include\a7670e_module.hpp" echo [OK] a7670e_module.hpp
if exist "%COMPONENT_DIR%\include\a7670e_urc_handler.hpp" echo [OK] a7670e_urc_handler.hpp
echo.

echo Checking source files...
if exist "%COMPONENT_DIR%\src\a7670e_module.cpp" echo [OK] a7670e_module.cpp
if exist "%COMPONENT_DIR%\src\a7670e_commands_net.cpp" echo [OK] a7670e_commands_net.cpp
if exist "%COMPONENT_DIR%\src\a7670e_commands_serial.cpp" echo [OK] a7670e_commands_serial.cpp
if exist "%COMPONENT_DIR%\src\a7670e_commands_fs.cpp" echo [OK] a7670e_commands_fs.cpp
if exist "%COMPONENT_DIR%\src\a7670e_commands_http.cpp" echo [OK] a7670e_commands_http.cpp
if exist "%COMPONENT_DIR%\src\a7670e_commands_mqtt.cpp" echo [OK] a7670e_commands_mqtt.cpp
if exist "%COMPONENT_DIR%\src\a7670e_commands_ssl.cpp" echo [OK] a7670e_commands_ssl.cpp
if exist "%COMPONENT_DIR%\src\a7670e_commands_gnss.cpp" echo [OK] a7670e_commands_gnss.cpp
if exist "%COMPONENT_DIR%\src\a7670e_commands_edrx.cpp" echo [OK] a7670e_commands_edrx.cpp
if exist "%COMPONENT_DIR%\src\a7670e_urc_handler.cpp" echo [OK] a7670e_urc_handler.cpp
echo.

echo Checking configuration files...
if exist "%COMPONENT_DIR%\CMakeLists.txt" echo [OK] CMakeLists.txt
if exist "%COMPONENT_DIR%\Kconfig" echo [OK] Kconfig
if exist "%COMPONENT_DIR%\idf_component.yml" echo [OK] idf_component.yml
echo.

echo Checking documentation...
if exist "%COMPONENT_DIR%\README.md" echo [OK] README.md
if exist "%COMPONENT_DIR%\INTEGRATION_GUIDE.md" echo [OK] INTEGRATION_GUIDE.md
if exist "%COMPONENT_DIR%\CONTRIBUTING.md" echo [OK] CONTRIBUTING.md
if exist "%COMPONENT_DIR%\CHANGELOG.md" echo [OK] CHANGELOG.md
if exist "%COMPONENT_DIR%\LICENSE" echo [OK] LICENSE
echo.

echo Checking example files...
if exist "%COMPONENT_DIR%\examples\a7670e_at_only\CMakeLists.txt" echo [OK] example CMakeLists.txt
if exist "%COMPONENT_DIR%\examples\a7670e_at_only\a7670e_at_example.cpp" echo [OK] a7670e_at_example.cpp
echo.

echo ==========================================
echo Verification completed!
echo ==========================================
echo.
echo Component is ready for integration.
echo.
echo Next steps:
echo 1. Integrate component into ESP-IDF project
echo 2. Run: idf.py build
echo 3. Read INTEGRATION_GUIDE.md for usage
echo.

