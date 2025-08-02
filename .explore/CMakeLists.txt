cmake_minimum_required(VERSION 3.24)
project(protobuf-explore)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)

install(TARGETS explore RUNTIME DESTINATION ${CMAKE_BINARY_DIR})