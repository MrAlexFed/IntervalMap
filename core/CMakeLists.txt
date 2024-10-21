cmake_minimum_required(VERSION 3.27)

add_library(interval_map_core INTERFACE)

target_include_directories(interval_map_core INTERFACE ${CMAKE_SOURCE_DIR}/core)

