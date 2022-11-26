project(ttn-otaa)

list(APPEND ${PROJECT_NAME}_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/${BOARD}/main.cpp"
)

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    # $<TARGET_OBJECTS:system>
    # $<TARGET_OBJECTS:radio>
    # $<TARGET_OBJECTS:peripherals>
    $<TARGET_OBJECTS:${BOARD}>
    $<TARGET_OBJECTS:ldl-library>
)

# undefined reference to `_exit'
#target_link_options(${PROJECT_NAME} PRIVATE --specs=nosys.specs)


# Add compile time definition for the mbed shield if set.
target_compile_definitions(${PROJECT_NAME} PUBLIC 
#    -D${MBED_RADIO_SHIELD}
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:ldl-library,INTERFACE_COMPILE_DEFINITIONS>>
)

target_include_directories(${PROJECT_NAME} PUBLIC
#     # $<BUILD_INTERFACE:$<TARGET_PROPERTY:system,INTERFACE_INCLUDE_DIRECTORIES>>
#     # $<BUILD_INTERFACE:$<TARGET_PROPERTY:radio,INTERFACE_INCLUDE_DIRECTORIES>>
#     # $<BUILD_INTERFACE:$<TARGET_PROPERTY:peripherals,INTERFACE_INCLUDE_DIRECTORIES>>
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:${BOARD},INTERFACE_INCLUDE_DIRECTORIES>>
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:ldl-library,INTERFACE_INCLUDE_DIRECTORIES>>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)


#target_link_libraries(${PROJECT_NAME} m)

#---------------------------------------------------------------------------------------
# Debugging and Binutils
#---------------------------------------------------------------------------------------

include(gdb-helper)
include(binutils-arm-none-eabi)

# Generate debugger configurations
generate_run_gdb_stlink(${PROJECT_NAME})
generate_run_gdb_openocd(${PROJECT_NAME})
generate_vscode_launch_openocd(${PROJECT_NAME})

# Print section sizes of target
print_section_sizes(${PROJECT_NAME})

# Create output in hex and binary format
create_bin_output(${PROJECT_NAME})
create_hex_output(${PROJECT_NAME})
