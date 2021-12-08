project(InteractionMessage)

cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDART 17)

add_compile_options(-Wall -Wpedantic -g3) #  -Werror
#add_compile_options(-lpthread) #-lpthread
#add_link_options(-lpthread)

find_package(Protobuf REQUIRED)
#find_package(Threads)



#add_library(MessageOperations STATIC project/src/receiveInteraction.cpp project/include/receiveInteraction.h project/src/sendInteraction.cpp project/include/sendInteraction.h)
#add_library(OperationEmulation STATIC project/src/operationEmulation.cpp project/include/operationEmulation.h ${PROTO_SRCS} ${PROTO_HDRS})
add_subdirectory(project/lib/protobufOperations)
add_subdirectory(project/lib/emulation)
#add_subdirectory(project/lib/operationEmulation)


add_executable(sendReceiveKeybMess project/src/sendReceiveMessage.cpp) #${PROTO_SRCS} ${PROTO_HDRS}
target_link_libraries(sendReceiveKeybMess protobufOperations) #${Protobuf_LIBRARIES}

add_executable(emulate project/src/emulate.cpp  )
target_link_libraries(emulate emulation protobufOperations) # ${Protobuf_LIBRARIES}

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(protobufTest project/tests/protobufTest.cpp )
target_link_libraries(protobufTest protobufOperations ${GTEST_LIBRARIES})
target_link_libraries(protobufTest gtest pthread) #!
# target_link_libraries(MESSAGE_TEST gtest pthread) #!