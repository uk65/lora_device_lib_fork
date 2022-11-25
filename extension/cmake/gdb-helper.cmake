# Get the path of this module
set(CURRENT_MODULE_DIR ${CMAKE_CURRENT_LIST_DIR})

#---------------------------------------------------------------------------------------
# Set tools
#---------------------------------------------------------------------------------------
set(GDB_BIN ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gdb)
if(NOT OPENOCD_BIN)
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
        set(OPENOCD_BIN "/usr/bin/openocd" CACHE STRING "OpenOCD executable")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)
        set(OPENOCD_BIN "/usr/local/bin/openocd" CACHE STRING "OpenOCD executable")
    endif()
endif()

#---------------------------------------------------------------------------------------
# Generates a GDB run script for debugging with STLINKv1/v2/v2-1 programmer and texane stlink tool.
# More infos check: https://github.com/texane/stlink
#---------------------------------------------------------------------------------------
function(generate_run_gdb_stlink TARGET)
    get_target_property(TARGET_NAME ${TARGET} NAME)
    configure_file(${CURRENT_MODULE_DIR}/stlink-run.gdb.in ${PROJECT_BINARY_DIR}/stlink-run.gdb @ONLY)
endfunction()

#---------------------------------------------------------------------------------------
# Generates a GDB run script for debugging with any supported programmer and openOCD.
#---------------------------------------------------------------------------------------
function(generate_run_gdb_openocd TARGET)
    get_target_property(TARGET_NAME ${TARGET} NAME)
    configure_file(${CURRENT_MODULE_DIR}/openocd-run.gdb.in ${PROJECT_BINARY_DIR}/openocd-run.gdb @ONLY)
endfunction()

#---------------------------------------------------------------------------------------
# Generates a Visual Studio Code launch configuration for debugging with openOCD.
#---------------------------------------------------------------------------------------
function(generate_vscode_launch_openocd TARGET)
    get_target_property(TARGET_NAME ${TARGET} NAME)

    # Available OpenOCD interfaces
    # Use stlink.cfg when stlink interface is built in.
    set(OPENOCD_INTERFACE_LIST stlink.cfg)
    set(OPENOCD_INTERFACE stlink.cfg CACHE STRING "Default OPENOCD Interface is stlink.cfg")
    set_property(CACHE OPENOCD_INTERFACE PROPERTY STRINGS ${OPENOCD_INTERFACE_LIST})

    # Available OpenOCD targets
    set(OPENOCD_TARGET_LIST stm32l1.cfg)
    set(OPENOCD_TARGET stm32l1.cfg CACHE STRING "Default OPENOCD Target is stm32l1.cfg")
    set_property(CACHE OPENOCD_TARGET PROPERTY STRINGS ${OPENOCD_TARGET_LIST})

    # Set the OPENOCD_TARGET and OPENOCD_INTERFACE variables according to BOARD
    if(BOARD STREQUAL heltec151)
        set(OPENOCD_INTERFACE stlink.cfg)
        set(OPENOCD_TARGET stm32l1.cfg)
    endif()

    configure_file(${CURRENT_MODULE_DIR}/launch.json.in ${CMAKE_SOURCE_DIR}/.vscode/launch.json @ONLY)
endfunction()
