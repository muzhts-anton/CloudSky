INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS src/keyboard_mouse_message.proto)
add_library(MessageOperations STATIC src/message_operations.cpp)
target_include_directories(MessageOperations PUBLIC include)
