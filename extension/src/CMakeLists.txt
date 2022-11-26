project(extension)

# set(BOARD_LIST heltec151)
# set(BOARD heltec151 CACHE STRING "Default target platform is heltec151")
# set_property(CACHE BOARD PROPERTY STRINGS ${BOARD_LIST})
#
# set(MBED_RADIO_SHIELD_LIST sx1261 sx1262 sx1272 sx1276 wl55)
# set(MBED_RADIO_SHIELD sx1276 CACHE STRING "Default MBED radio shield is sx1276")
# set_property(CACHE MBED_RADIO_SHIELD PROPERTY STRINGS ${MBED_RADIO_SHIELD_LIST})
#
# set(REGION_LIST REGION_EU433 REGION_EU868 REGION_US915 REGION_AU915)
# set(REGION REGION_EU868 CACHE STRING "Default region ist REGION_EU868")
# set_property(CACHE REGION PROPERTY STRINGS ${REGION_LIST})
#
# set(APPLICATION_LIST ttn-otaa)
# set(APPLICATION ttn-otaa CACHE STRING "Default Application is ttn-otaa")
# set_property(CACHE APPLICATION PROPERTY STRINGS ${APPLICATION_LIST})

# Switch for debugger support.
option(USE_DEBUGGER "Use Debugger" ON)

#---------------------------------------------------------------------------------------
# Applications
#---------------------------------------------------------------------------------------

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ldl)

#---------------------------------------------------------------------------------------
# Target Boards
#---------------------------------------------------------------------------------------

if(BOARD STREQUAL heltec151)
    set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/boards/heltec151/cmsis/stm32l151ccux_flash.ld)
     include(stm32l1)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/boards/heltec151)
#     set(RADIO sx1276 CACHE INTERNAL "Radio sx1276 selected")
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



