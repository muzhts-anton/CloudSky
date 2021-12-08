INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR}) #
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}) #
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS src/KeyboardMouseMessage.proto) #

add_library(protobufOperations STATIC src/messageOperations.cpp include/messageOperations.h  ${PROTO_SRCS} ${PROTO_HDRS})

target_include_directories(protobufOperations PUBLIC include)

target_link_libraries(protobufOperations PUBLIC ${Protobuf_LIBRARIES}) # MessageOperations