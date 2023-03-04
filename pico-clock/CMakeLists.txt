cmake_minimum_required(VERSION 3.23)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()

include(pico_sdk_import.cmake)

project(pico C CXX ASM)

set(CMAKE_C_STANDARD 11)

# Initialize the SDK
pico_sdk_init()

add_executable(pico main.c)
target_link_libraries(pico  pico_stdlib hardware_clocks)
pico_enable_stdio_usb(pico 1)
pico_enable_stdio_uart(pico 0)
# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(pico)