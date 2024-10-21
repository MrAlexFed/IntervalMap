cmake_minimum_required(VERSION 3.27)

add_library(boost_ut INTERFACE)

target_include_directories(boost_ut INTERFACE ${CMAKE_SOURCE_DIR}/thirdparty/boost_ut)