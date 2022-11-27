project(heltec151)

enable_language(ASM)

#set(USE_HAL "1")

list(APPEND ${PROJECT_NAME}_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/rcc-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/spi-board.c"
#    "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/utilities.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmsis/startup_stm32l151ccux.s"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmsis/system_stm32l1xx.c"
)

if(USE_HAL STREQUAL "1")
    list(APPEND ${PROJECT_NAME}_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_adc.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_adc_ex.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_cortex.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_dma.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ex.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_gpio.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_i2c.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr_ex.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc_ex.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rtc.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rtc_ex.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_spi.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_spi_ex.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_uart.c"
    )    
endif()

add_library(${PROJECT_NAME} OBJECT EXCLUDE_FROM_ALL ${${PROJECT_NAME}_SOURCES})

target_compile_definitions(${PROJECT_NAME} PUBLIC 
    STM32L151xC 
#    ${MBED_RADIO_SHIELD}
)

if(USE_HAL STREQUAL "1")
    target_compile_definitions(${PROJECT_NAME} PUBLIC 
        USE_HAL_DRIVER 
    )
endif()

# Add define if debbuger support is enabled
#target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<BOOL:${USE_DEBUGGER}>:USE_DEBUGGER>)

# Add define if radio debug pins support is enabled
#target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<BOOL:${USE_RADIO_DEBUG}>:USE_RADIO_DEBUG>)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmsis
    ${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32
    ${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/cmsis
    $<TARGET_PROPERTY:board,INTERFACE_INCLUDE_DIRECTORIES>
#     # $<TARGET_PROPERTY:system,INTERFACE_INCLUDE_DIRECTORIES>
#     # $<TARGET_PROPERTY:radio,INTERFACE_INCLUDE_DIRECTORIES>
#     # $<TARGET_PROPERTY:peripherals,INTERFACE_INCLUDE_DIRECTORIES>
)

if(USE_HAL STREQUAL "1")
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../mcu/stm32/STM32L1xx_HAL_Driver/Inc
    )
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
