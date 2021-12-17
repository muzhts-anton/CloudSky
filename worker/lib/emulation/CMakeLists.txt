INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR}) #
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}) #
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS src/KeyboardMouseMessage.proto) #

add_library(emulation STATIC src/operationEmulation.cpp include/operationEmulation.h ${PROTO_SRCS} ${PROTO_HDRS} ) # src/messageOperations.cpp include/messageOperations.h

target_include_directories(emulation PUBLIC include ../../build/lib/emulation)

target_link_libraries(emulation PUBLIC ${Protobuf_LIBRARIES}) # ${Protobuf_LIBRARIES}