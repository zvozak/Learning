cmake_minimum_required(VERSION 3.26)
project(hackerrank)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(hackerrank_run ${SOURCE_FILES})

include_directories(hackerrank_lib)
add_subdirectory(hackerrank_lib)

target_link_libraries(hackerrank_run hackerrank_lib)

add_subdirectory(Google_tests)