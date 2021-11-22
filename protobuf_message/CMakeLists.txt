project(InteractionMessage)

cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDART 17)
FIND_PACKAGE(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS project/src/keyboard_mouse_message.proto)


add_library(MessageOperations STATIC project/src/message_operations.cpp project/include/message_operations.h)


add_executable(send_receive_keyb_m project/src/send_receive_message.cpp  ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(send_receive_keyb_m MessageOperations ${Protobuf_LIBRARIES})


# enable_testing()
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIR})
# add_executable(message_test project/tests/message_test.cpp project/src/message_operations.cpp)

# target_link_libraries(message_test ${GTEST_LIBRARIES} MessageOperations)
# target_link_libraries(message_test gtest pthread) #!