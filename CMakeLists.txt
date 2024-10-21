cmake_minimum_required(VERSION 3.27)
project(interval_map LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(core)
add_subdirectory(test)
add_subdirectory(thirdparty/boost_ut)