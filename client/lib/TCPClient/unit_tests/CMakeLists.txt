add_executable(clientProtocolTest src/mainTest.cpp src/TCPClientTest.cpp src/UDPClientTest.cpp)

target_link_libraries(clientProtocolTest clientSockets GTest::Main gcov)

add_test(NAME serverTest COMMAND serverTest)