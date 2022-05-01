find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_library(ServerConnection STATIC src/TCPServerSocket.cpp  src/UDPServerSocket.cpp 
src/Server.cpp  src/Connection.cpp
include/TCPServerSocket.h include/Server.h include/Connection.h)

target_include_directories(ServerConnection PUBLIC include)
target_include_directories(ServerConnection  PUBLIC ../dbOperations/include)

target_link_libraries(ServerConnection ${PostgreSQL_LIBRARIES} dbOperations)

# enable_testing()

# add_subdirectory(unit_tests)

# target_link_libraries(TCPServer gcov)