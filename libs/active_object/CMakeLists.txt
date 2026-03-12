set(MY_NAME active_object)

add_library(${MY_NAME})

target_sources(${MY_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/active_object.cpp
)

target_include_directories(${MY_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(${MY_NAME}
    PRIVATE
        ${myCompileOptions}
)

target_link_libraries(${MY_NAME}
    PUBLIC
        data_struct
)