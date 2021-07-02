cmake_minimum_required(VERSION 3.13)

set(CMAKE_TOOLCHAIN_FILE armgcc.cmake)

ENABLE_LANGUAGE(ASM)

project(MinimalLedBlinky VERSION 1.0)

set (TARGET min)

add_executable(${TARGET}.elf
    ../minimal/blinky.c
    ../minimal/system_MK66F18.c
    startup_MK66F18.S
)

target_include_directories(${TARGET}.elf PUBLIC ../minimal/CMSIS/Include)

target_link_options(${TARGET}.elf PRIVATE -T ${CMAKE_CURRENT_SOURCE_DIR}/MK66FN2M0xxx18_flash.ld -Wl,-Map=nxp.map)

# Post processing command to create a hex file
add_custom_command(TARGET ${TARGET}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary  ${TARGET}.elf  ${TARGET}.bin
        COMMENT "Invoking: Hexdump")
