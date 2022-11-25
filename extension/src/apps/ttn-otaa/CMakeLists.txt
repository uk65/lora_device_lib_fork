project(ttn-otaa)
cmake_minimum_required(VERSION 3.6)

# Allow selection of region
option(REGION_EU433 "Region EU433" OFF)
option(REGION_EU868 "Region EU868" ON)
option(REGION_US915 "Region US915" OFF)
option(REGION_AU915 "Region AU915" OFF)
set(REGION_LIST REGION_EU433 REGION_EU868 REGION_US915 REGION_AU915)

file(GLOB ${PROJECT_NAME}_SOURCES "${CMAKE_CURRENT_LIST_DIR}/${BOARD}/*.cpp")

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    # $<TARGET_OBJECTS:system>
    # $<TARGET_OBJECTS:radio>
    # $<TARGET_OBJECTS:peripherals>
    #$<TARGET_OBJECTS:${BOARD}>
)

foreach( REGION ${REGION_LIST} )
    if(${REGION})
        target_compile_definitions(${PROJECT_NAME} PUBLIC -D"${REGION}")
    endif()
endforeach()

# Add compile time definition for the mbed shield if set.
target_compile_definitions(${PROJECT_NAME} PUBLIC -D${MBED_RADIO_SHIELD})

target_include_directories(${PROJECT_NAME} PUBLIC
    # $<BUILD_INTERFACE:$<TARGET_PROPERTY:system,INTERFACE_INCLUDE_DIRECTORIES>>
    # $<BUILD_INTERFACE:$<TARGET_PROPERTY:radio,INTERFACE_INCLUDE_DIRECTORIES>>
    # $<BUILD_INTERFACE:$<TARGET_PROPERTY:peripherals,INTERFACE_INCLUDE_DIRECTORIES>>
    #$<BUILD_INTERFACE:$<TARGET_PROPERTY:${BOARD},INTERFACE_INCLUDE_DIRECTORIES>>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

target_link_libraries(${PROJECT_NAME} m)

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
