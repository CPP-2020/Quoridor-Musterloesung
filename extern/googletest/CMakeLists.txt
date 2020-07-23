# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
add_executable(
    Google_Tests_run
    testcases/test_sample.cpp
    testcases/graph_tests.cpp
    testcases/gamelib_tests.cpp testcases/GameRules_tests.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main GraphLib LoggerLib GameLib)
