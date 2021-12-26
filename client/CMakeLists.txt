cmake_minimum_required(VERSION 3.5)

project(CloudSky_MyClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

link_libraries(-lpq)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Werror -Wextra -Wpedantic -Wno-deprecated-declarations -c -g -lpqxx -L/usr/lib/x86_64-linux-gnu/libpq -lpq)
add_link_options(-lpqxx -lpq )

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(PostgreSQL REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(CloudSky_MyClient ${SDL2_INCLUDE_DIRS})

FIND_PACKAGE(Protobuf REQUIRED)
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS}/inc/)

add_subdirectory(lib/clientConnection)
add_subdirectory(lib/protobufOperations)
add_subdirectory(lib/dbOperations)
add_subdirectory(lib/ui)


add_executable(CloudSky_MyClient src/main.cpp)

target_include_directories(CloudSky_MyClient PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(CloudSky_MyClient Qt5::Widgets ui avcodec avformat swscale avutil ${SDL2_LIBRARIES} clientConnection protobufOperations ${PostgreSQL_LIBRARIES} dbOperations) 



set_target_properties(CloudSky_MyClient PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

