project(InteractionMessage)

cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDART 17)

add_compile_options(-Wall -Werror -Wpedantic -g3)
#add_compile_options(-lpthread) #-lpthread
#add_link_options(-lpthread)

FIND_PACKAGE(Protobuf REQUIRED)
#find_package(Threads)



#add_library(MessageOperations STATIC project/src/receiveInteraction.cpp project/include/receiveInteraction.h project/src/sendInteraction.cpp project/include/sendInteraction.h)
#add_library(OperationEmulation STATIC project/src/operationEmulation.cpp project/include/operationEmulation.h ${PROTO_SRCS} ${PROTO_HDRS})
add_subdirectory(project/lib/protobufOperations)

add_executable(sendReceiveKeybMess project/src/sendReceiveMessage.cpp) #${PROTO_SRCS} ${PROTO_HDRS}
target_link_libraries(sendReceiveKeybMess protobufOperations ) #${Protobuf_LIBRARIES}

#add_executable(Emulate project/src/emulate.cpp  )
#arget_link_libraries(Emulate OperationEmulation MessageOperations ${Protobuf_LIBRARIES})


# enable_testing()
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIR})
# add_executable(MESSAGE_TEST project/tests/MESSAGE_TEST.cpp project/src/messageOperations.cpp)

# target_link_libraries(MESSAGE_TEST ${GTEST_LIBRARIES} MessageOperations)
# target_link_libraries(MESSAGE_TEST gtest pthread) #!