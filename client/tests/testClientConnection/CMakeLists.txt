add_executable(clientConnectionTest src/main.cpp src/createFilesToSend.cpp)

target_link_libraries(clientConnectionTest clientConnection GTest::Main gcov)

target_include_directories(clientConnectionTest PUBLIC include)

add_test(NAME clientConnectionTest COMMAND clientConnectionTest)