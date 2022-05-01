INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR}) 
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}) 
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS src/dbMessages.proto) 

add_library(dbOperations STATIC src/dbOperations.cpp include/dbOperations.h   ${PROTO_SRCS} ${PROTO_HDRS}) #${PROTO_SRCS} ${PROTO_HDRS}

target_include_directories(dbOperations PUBLIC ../../build/lib/dbOperations)

target_include_directories(dbOperations PUBLIC include)

target_link_libraries(dbOperations PUBLIC ${Protobuf_LIBRARIES})