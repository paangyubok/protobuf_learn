include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(PROTOBUF_LEARN_DIR ${PROJECT_SOURCE_DIR}/..)
list(APPEND CMAKE_PREFIX_PATH ${PROTOBUF_LEARN_DIR}/.build/install_dir)
find_package(GTest REQUIRED)
find_package(protobuf CONFIG REQUIRED)
message(STATUS "Using Protocol Buffers ${protobuf_VERSION}")

execute_process(
  COMMAND bash "-c" "find ${CMAKE_SOURCE_DIR} \\( -name '*.pb.h' -o -name '*.pb.cc' \\) | xargs -n1 rm -f"
)

file(GLOB proto_files *.proto)
protobuf_generate(
    LANGUAGE cpp
    PROTOS ${proto_files}
    PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    OUT_VAR PB_SRCS
)

set(executable_name explore)
add_executable(${executable_name})
target_sources(${executable_name} PRIVATE
  main.cc
  ${PB_SRCS}
)

target_link_libraries(${executable_name} protobuf::libprotobuf)