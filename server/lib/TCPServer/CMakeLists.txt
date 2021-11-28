add_library(TCPServer STATIC src/TCPServerSocket.cpp src/Server.cpp 
include/TCPServerSocket.h include/Server.h)

target_include_directories(TCPServer PUBLIC include)

# enable_testing()

# add_subdirectory(unit_tests)

# target_link_libraries(TCPServer gcov)