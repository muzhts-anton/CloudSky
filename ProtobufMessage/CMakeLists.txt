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


add_executable(sendReceiveKeybMessTest project/tests/sendReceiveMessageTest.cpp) 
target_link_libraries(sendReceiveKeybMessTest protobufOperations) 

add_executable(emulateTest project/tests/emulateTest.cpp  )
target_link_libraries(emulateTest emulation protobufOperations) 

add_executable(serverDBTest project/tests/serverDBTest.cpp) 
target_include_directories(serverDBTest PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(serverDBTest PRIVATE ${PostgreSQL_LIBRARIES} dbOperations)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(protobufGTest project/tests/protobufTest.cpp )
target_link_libraries(protobufGTest protobufOperations gtest pthread ${GTEST_LIBRARIES})
#target_include_directories(protobufTest PUBLIC lib/emulation/include lib/protobufOperations/include)

add_executable(emulateGTest project/tests/emulateInteractionTest.cpp )
target_link_libraries(emulateGTest protobufOperations emulation gtest pthread ${GTEST_LIBRARIES})
target_include_directories(emulateGTest PUBLIC project/lib/emulation/include project/lib/protobufOperations/include)
