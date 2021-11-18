add_executable(clientTest src/maintest.cpp src/clienttest.cpp)

target_link_libraries(clientTest GTest::Main)

add_test(NAME clientTest COMMAND clientTest)
