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



#set(CMAKE_C_FLAGS "pkg-config --cflags --libs protobuf")
#NCLUDE(FindProtobuf)
#FIND_PACKAGE(Protobuf REQUIRED)
#INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})
#PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER message.proto)
#ADD_LIBRARY(proto ${PROTO_HEADER} ${PROTO_SRC})

#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

#add_executable(send_receive_keyb_m send_receive_message.cpp)



#add_executable(send_receive_keyb_m send_receive_message.cpp keyboard_mouse_message.pb.cc)
