project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run fraudulent_activity_test.cpp counting_inversions_test.cpp triplets_test.cpp utils.cpp common_child_test.cpp)

target_link_libraries(Google_Tests_run hackerrank_lib)

target_link_libraries(Google_Tests_run gtest gtest_main)