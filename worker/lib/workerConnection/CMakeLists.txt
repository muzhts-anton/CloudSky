add_library(workerConnection STATIC src/TCPWorkerSocket.cpp  src/UDPWorkerSocket.cpp src/Worker.cpp 
include/TCPWorkerSocket.h include/Worker.h)

target_include_directories(workerConnection PUBLIC include)

# enable_testing()

# add_subdirectory(unit_tests)

# target_link_libraries(TCPServer gcov)