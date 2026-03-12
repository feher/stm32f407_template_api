set(MY_NAME stm32f407_drivers)

add_library(${MY_NAME})

target_include_directories(${MY_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(${MY_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/util.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/clocks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/generic_irq_handlers.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/spi.cpp       
)

target_compile_options(${MY_NAME}
    PRIVATE
        ${myCompileOptions}
)

target_link_libraries(${MY_NAME}
    PUBLIC
        stm32f407_bitapi
)
