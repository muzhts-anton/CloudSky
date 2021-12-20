project(InteractionMessage)

cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDART 17)

link_libraries(-lpq)
add_compile_options(-Wall -Wpedantic -g3 -Werror -c -g -lpqxx -L/usr/lib/x86_64-linux-gnu/libpq -lpq)
add_link_options(-lpqxx -lpq )

find_package(Protobuf REQUIRED)
find_package(PostgreSQL REQUIRED)

add_subdirectory(project/lib/protobufOperations)
add_subdirectory(project/lib/emulation)
add_subdirectory(project/lib/dbOperations)


add_executable(sendReceiveKeybMess project/src/sendReceiveMessage.cpp) 
target_link_libraries(sendReceiveKeybMess protobufOperations) 

add_executable(emulate project/src/emulate.cpp  )
target_link_libraries(emulate emulation protobufOperations) 


enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(protobufTest project/tests/protobufTest.cpp )
target_link_libraries(protobufTest protobufOperations gtest pthread ${GTEST_LIBRARIES})
#target_include_directories(protobufTest PUBLIC lib/emulation/include lib/protobufOperations/include)

add_executable(emulateTest project/tests/emulateInteractionTest.cpp )
target_link_libraries(emulateTest protobufOperations emulation gtest pthread ${GTEST_LIBRARIES})
target_include_directories(emulateTest PUBLIC project/lib/emulation/include project/lib/protobufOperations/include)

add_executable(serverDB project/src/serverDB.cpp) 
target_include_directories(serverDB PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(serverDB PRIVATE ${PostgreSQL_LIBRARIES} dbOperations)