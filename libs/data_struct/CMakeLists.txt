set(MY_NAME data_struct)

add_library(${MY_NAME} INTERFACE)

target_include_directories(${MY_NAME}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(${MY_NAME}
    INTERFACE
        ${myCompileOptions}
)
