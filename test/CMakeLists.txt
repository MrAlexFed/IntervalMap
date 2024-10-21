cmake_minimum_required(VERSION 3.27)

add_executable(interval_map_tests interval_map_tests.cpp)

target_link_libraries(interval_map_tests PRIVATE interval_map_core boost_ut)

add_test(interval_map_tests interval_map_tests)

enable_testing()