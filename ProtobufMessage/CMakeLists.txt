project(InteractionMessage)

cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDART 17)
FIND_PACKAGE(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS project/src/KeyboardMouseMessage.proto)


add_library(MessageOperations STATIC project/src/MessageOperations.cpp project/include/MessageOperations.h ${Protobuf_LIBRARIES} )
#add_library(MessageOperations STATIC project/src/ReceiveInteraction.cpp project/include/ReceiveInteraction.h project/src/SendInteraction.cpp project/include/SendInteraction.h)
add_library(OperationEmulation STATIC project/src/OperationEmulation.cpp project/include/OperationEmulation.h)


add_executable(SendReceiveKeybMess project/src/SendReceiveMessage.cpp  ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(SendReceiveKeybMess MessageOperations ${Protobuf_LIBRARIES})

add_executable(Emulate project/src/Emulate.cpp  ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(Emulate OperationEmulation MessageOperations ${Protobuf_LIBRARIES})


# enable_testing()
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIR})
# add_executable(MESSAGE_TEST project/tests/MESSAGE_TEST.cpp project/src/MessageOperations.cpp)

# target_link_libraries(MESSAGE_TEST ${GTEST_LIBRARIES} MessageOperations)
# target_link_libraries(MESSAGE_TEST gtest pthread) #!