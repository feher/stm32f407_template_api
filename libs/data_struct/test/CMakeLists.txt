cmake_minimum_required(VERSION 3.20)

project("data_struct_test")

enable_language(CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# START - Fetch GoogleTest
#  set the timestamps of extracted contents to the time of extraction
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.tar.gz
)
FetchContent_MakeAvailable(googletest)
# END - Fetch GoogleTest

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/data_struct)

enable_testing()

add_executable(${CMAKE_PROJECT_NAME}
    queue_1_test.cpp
    queue_2_test.cpp
    queue_3_test.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        GTest::gtest_main
        data_struct
)

# target_compile_options(${CMAKE_PROJECT_NAME}
#     PRIVATE
#         -fsanitize=thread
# )
# 
# target_link_options(${CMAKE_PROJECT_NAME}
#     PRIVATE
#         -fsanitize=thread
# )

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME})
