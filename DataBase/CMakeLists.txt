project(InteractionMessage)

cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDART 17)

find_package(PostgreSQL REQUIRED)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -L/path/to/libpq -lpq")
link_libraries(-lpq)
add_compile_options(-Wall -Wpedantic -c -g -g3 -lpqxx -L/usr/lib/x86_64-linux-gnu/libpq -lpq ) #-Werror
add_link_options(-lpqxx -lpq )
#link_directories()

set(PQXX /usr/local/include/pqxx)


add_subdirectory(project/lib/dbOperations)

add_executable(serverDB project/src/serverDB.cpp) 
target_include_directories(serverDB PRIVATE ${PostgreSQL_INCLUDE_DIRS})
#target_include_directories(serverDB PUBLIC project/lib/dbOperations/include())
target_link_libraries(serverDB PRIVATE ${PostgreSQL_LIBRARIES})
#target_link_libraries(serverDB PRIVATE PRIVATE PostgreSQL::PostgreSQL)
target_link_libraries(serverDB PRIVATE dbOperations)