add_executable(workerConnectionTest src/main.cpp src/createFilesToSend.cpp)

target_link_libraries(workerConnectionTest workerConnection GTest::Main gcov)

target_include_directories(workerConnectionTest PUBLIC include)

add_test(NAME workerConnectionTest COMMAND workerConnectionTest)