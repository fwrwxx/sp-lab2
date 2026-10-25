#!/bin/sh
set -e
if grep -rn "stm32c0xx_hal.h\|stm32c0xx_hal_" firmware/App/ firmware/Devices/ 2>/dev/null; then
    echo "DEPENDENCY VIOLATION: App/ or Devices/ includes HAL"
    exit 1
fi
echo "Dependency check: OK"