add_executable(serverTest src/mainTest.cpp src/serverTest.cpp)

target_link_libraries(serverTest serverSockets GTest::Main gcov)

add_test(NAME serverTest COMMAND serverTest)