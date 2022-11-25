project(extension-src)
cmake_minimum_required(VERSION 3.6)

set(BOARD_LIST heltec151)
set(BOARD heltec151 CACHE STRING "Default target platform is heltec151")
set_property(CACHE BOARD PROPERTY STRINGS ${BOARD_LIST})

set(MBED_RADIO_SHIELD_LIST sx1261 sx1262 sx1272 sx1276 wl55)
set(MBED_RADIO_SHIELD sx1276 CACHE STRING "Default MBED radio shield is sx1276")
set_property(CACHE MBED_RADIO_SHIELD PROPERTY STRINGS ${MBED_RADIO_SHIELD_LIST})

set(REGION_LIST REGION_EU433 REGION_EU868 REGION_US915 REGION_AU915)
set(REGION REGION_EU868 CACHE STRING "Default region ist REGION_EU868")
set_property(CACHE REGION PROPERTY STRINGS ${REGION_LIST})

set(APPLICATION_LIST ttn-otaa)
set(APPLICATION ttn-otaa CACHE STRING "Default Application is ttn-otaa")
set_property(CACHE APPLICATION PROPERTY STRINGS ${APPLICATION_LIST})

# Switch for debugger support.
option(USE_DEBUGGER "Use Debugger" ON)

#---------------------------------------------------------------------------------------
# Target Boards
#---------------------------------------------------------------------------------------

if(BOARD STREQUAL HeltecLoRa151)
    
    set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/boards/heltec151/cmsis/stm32l151ccux_flash.ld)
    include(stm32l1)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/boards/heltec151)
    set(RADIO sx1276 CACHE INTERNAL "Radio sx1276 selected")

endif()

#---------------------------------------------------------------------------------------
# Boards
#---------------------------------------------------------------------------------------

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/boards)

#---------------------------------------------------------------------------------------
# Applications
#---------------------------------------------------------------------------------------

if(APPLICATION STREQUAL ttn-otaa)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/ttn-otaa)

endif()

#---------------------------------------------------------------------------------------
# Library
#---------------------------------------------------------------------------------------

if(MBED_RADIO_SHIELD STREQUAL sx1261)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_SX1261)
elseif(MBED_RADIO_SHIELD STREQUAL sx1262)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_SX1262)
elseif(MBED_RADIO_SHIELD STREQUAL sx1272)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_SX1272)
elseif(MBED_RADIO_SHIELD STREQUAL sx1276)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_SX1276)
elseif(MBED_RADIO_SHIELD STREQUAL wl55)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_WL55)
endif()

if(REGION STREQUAL REGION_EU433)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_EU_433)
elseif(REGION STREQUAL REGION_EU868)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_EU_863_870)
elseif(REGION STREQUAL REGION_EU868)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_US_902_928)
elseif(REGION STREQUAL REGION_EU868)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_AU_915_928)
endif()

# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_L2_1_0_3)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_L2_1_0_4)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_L2_1_1)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_LITTLE_ENDIAN)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_RADIO_DEBUG)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_CLASS_B)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_PARAM_TPS)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_PARAM_A)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_PARAM_B)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_PARAM_ADVANCE)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_DISABLE_SF12)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_DISABLE_TX_PARAM_SETUP)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_OTAA_DITHER)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_ABP)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_TEST_MODE)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_DISABLE_DEVICE_TIME)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_STATIC_RX_BUFFER)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_DISABLE_LINK_CHECK)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_TRACE_DISABLED)
# target_compile_definitions(${PROJECT_NAME} PUBLIC -DLDL_ENABLE_ERRATA_A1)

list(APPEND ${PROJECT_NAME}_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_aes.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_cmac.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_ctr.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_frame.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_mac_commands.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_mac.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_ops.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_radio.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_region.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_sm.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_stream.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_sx126x.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src/ldl_sx127x.c"
)

#file(GLOB ${PROJECT_NAME}_SOURCES
#    "${CMAKE_CURRENT_SOURCE_DIR}/../../*.c"
#)

add_library(${PROJECT_NAME} OBJECT EXCLUDE_FROM_ALL ${${PROJECT_NAME}_SOURCES})

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    #$<TARGET_PROPERTY:peripherals,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:board,INTERFACE_INCLUDE_DIRECTORIES>
)

