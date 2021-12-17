add_library(ClientConnection STATIC src/TCPClientSocket.cpp  src/UDPClientSocket
include/UDPClientSocket.h include/TCPClientSocket.h)

target_include_directories(ClientConnection PUBLIC include)

# enable_testing()

# add_subdirectory(unit_tests)

# target_link_libraries(TCPClient gcov)