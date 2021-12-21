INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR}) 
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}) 
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS src/KeyboardMouseMessage.proto) 

add_library(emulation STATIC src/operationEmulation.cpp include/operationEmulation.h ${PROTO_SRCS} ${PROTO_HDRS} )

target_include_directories(emulation PUBLIC include)
target_include_directories(protobufOperations PUBLIC ../../../build/project/lib/protobufOperations)

target_link_libraries(emulation PUBLIC ${Protobuf_LIBRARIES}) 