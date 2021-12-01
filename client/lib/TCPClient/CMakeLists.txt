add_library(TCPClient STATIC src/TCPClientSocket.cpp include/TCPClientSocket.h)

target_include_directories(TCPClient PUBLIC include)

# enable_testing()

# add_subdirectory(unit_tests)

# target_link_libraries(TCPClient gcov)