enable_testing()
file(GLOB_RECURSE PROJECT_SOURCES "*.cpp")
add_executable(utest ${PROJECT_SOURCES})
target_link_libraries(utest PRIVATE GTest::gtest_main GTest::gmock_main)
