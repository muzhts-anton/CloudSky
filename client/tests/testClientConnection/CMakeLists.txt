add_executable(clientConnectionTest src/main.cpp src/createFilesToSend.cpp)

target_link_libraries(clientConnectionTest ClientConnection GTest::Main gcov)

add_test(NAME clientConnectionTest COMMAND clientConnectionTest)