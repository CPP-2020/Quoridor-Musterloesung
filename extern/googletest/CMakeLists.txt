# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
add_executable(
    Google_Tests_run
    testcases/Ui_test.cpp
    testcases/graph_tests.cpp
    testcases/gamelib_tests.cpp 
    testcases/GameRules_tests.cpp 
    testcases/PlaceBorderDecision_test.cpp
    testcases/MovePlayerDecision_test.cpp
    testcases/Ui_test.cpp
    testcases/SmartBot_test.cpp)

target_link_libraries(Google_Tests_run gtest gtest_main GraphLib LoggerLib GameLib)
