cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS
    ../..
    ../../../esp_modem)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(a7670e_build_smoke)
