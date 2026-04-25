#!/bin/bash
# Verification Script for A7670E Component

echo "=========================================="
echo "A7670E Modem Component Verification"
echo "=========================================="
echo ""

COMPONENT_DIR="components/a7670e_modem"
ERRORS=0
WARNINGS=0

# Helper functions
check_file() {
    if [ -f "$1" ]; then
        echo "✓ $1"
        return 0
    else
        echo "✗ MISSING: $1"
        ERRORS=$((ERRORS + 1))
        return 1
    fi
}

check_dir() {
    if [ -d "$1" ]; then
        echo "✓ Directory: $1"
        return 0
    else
        echo "✗ MISSING DIRECTORY: $1"
        ERRORS=$((ERRORS + 1))
        return 1
    fi
}

# Check directory structure
echo "Checking directory structure..."
check_dir "$COMPONENT_DIR"
check_dir "$COMPONENT_DIR/include"
check_dir "$COMPONENT_DIR/src"
check_dir "$COMPONENT_DIR/examples"
check_dir "$COMPONENT_DIR/examples/a7670e_at_only"
echo ""

# Check header files
echo "Checking header files..."
check_file "$COMPONENT_DIR/include/a7670e_types.hpp"
check_file "$COMPONENT_DIR/include/a7670e_module.hpp"
check_file "$COMPONENT_DIR/include/a7670e_urc_handler.hpp"
echo ""

# Check source files
echo "Checking source files..."
check_file "$COMPONENT_DIR/src/a7670e_module.cpp"
check_file "$COMPONENT_DIR/src/a7670e_commands_net.cpp"
check_file "$COMPONENT_DIR/src/a7670e_commands_serial.cpp"
check_file "$COMPONENT_DIR/src/a7670e_commands_fs.cpp"
check_file "$COMPONENT_DIR/src/a7670e_commands_http.cpp"
check_file "$COMPONENT_DIR/src/a7670e_commands_mqtt.cpp"
check_file "$COMPONENT_DIR/src/a7670e_commands_ssl.cpp"
check_file "$COMPONENT_DIR/src/a7670e_commands_gnss.cpp"
check_file "$COMPONENT_DIR/src/a7670e_commands_edrx.cpp"
check_file "$COMPONENT_DIR/src/a7670e_urc_handler.cpp"
echo ""

# Check configuration files
echo "Checking configuration files..."
check_file "$COMPONENT_DIR/CMakeLists.txt"
check_file "$COMPONENT_DIR/Kconfig"
check_file "$COMPONENT_DIR/idf_component.yml"
echo ""

# Check documentation
echo "Checking documentation..."
check_file "$COMPONENT_DIR/README.md"
check_file "$COMPONENT_DIR/INTEGRATION_GUIDE.md"
check_file "$COMPONENT_DIR/CONTRIBUTING.md"
check_file "$COMPONENT_DIR/CHANGELOG.md"
check_file "$COMPONENT_DIR/LICENSE"
echo ""

# Check example files
echo "Checking example files..."
check_file "$COMPONENT_DIR/examples/a7670e_at_only/CMakeLists.txt"
check_file "$COMPONENT_DIR/examples/a7670e_at_only/a7670e_at_example.cpp"
echo ""

# Check content of important files
echo "Checking file contents..."

# Check if CMakeLists.txt has all sources
if grep -q "a7670e_urc_handler.cpp" "$COMPONENT_DIR/CMakeLists.txt"; then
    echo "✓ CMakeLists.txt contains all source files"
else
    echo "✗ CMakeLists.txt missing source files"
    WARNINGS=$((WARNINGS + 1))
fi

# Check if module header has all method declarations
if grep -q "mqtt_cfg_argtopic" "$COMPONENT_DIR/include/a7670e_module.hpp"; then
    echo "✓ a7670e_module.hpp contains MQTT argtopic method"
else
    echo "✗ a7670e_module.hpp missing MQTT argtopic method"
    ERRORS=$((ERRORS + 1))
fi

# Check types
if grep -q "enum class RegStat" "$COMPONENT_DIR/include/a7670e_types.hpp"; then
    echo "✓ a7670e_types.hpp contains RegStat enum"
else
    echo "✗ a7670e_types.hpp missing RegStat enum"
    ERRORS=$((ERRORS + 1))
fi

if grep -q "struct MqttMessage" "$COMPONENT_DIR/include/a7670e_types.hpp"; then
    echo "✓ a7670e_types.hpp contains MqttMessage struct"
else
    echo "✗ a7670e_types.hpp missing MqttMessage struct"
    ERRORS=$((ERRORS + 1))
fi

echo ""

# Summary
echo "=========================================="
echo "Verification Summary"
echo "=========================================="
echo "Errors: $ERRORS"
echo "Warnings: $WARNINGS"

if [ $ERRORS -eq 0 ]; then
    echo ""
    echo "✓ All checks passed! Component is ready for integration."
    echo ""
    echo "Next steps:"
    echo "1. Copy component to ESP-IDF project"
    echo "2. Run 'idf.py build' to compile"
    echo "3. Check example in examples/a7670e_at_only/"
    echo "4. Read INTEGRATION_GUIDE.md for usage"
    exit 0
else
    echo ""
    echo "✗ Verification failed. Please fix the missing files."
    exit 1
fi

