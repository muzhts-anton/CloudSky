add_library(clientConnection STATIC src/TCPClientSocket.cpp  src/UDPClientSocket
include/UDPClientSocket.h include/TCPClientSocket.h)

target_include_directories(clientConnection PUBLIC include)

# enable_testing()

# add_subdirectory(unit_tests)

# target_link_libraries(TCPClient gcov)