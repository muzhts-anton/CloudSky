cmake_minimum_required(VERSION 3.5)

project(CloudSky_MyClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Werror -Wextra -Wpedantic)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# FIND_PACKAGE( Qt5Multimedia REQUIRED )
# FIND_PACKAGE( Qt5MultimediaWidgets REQUIRED )
# SET(QT_USE_QTMULTIMEDIA TRUE)
# SET(QT_USE_QTMULTIMEDIAWIDGETS TRUE)

# FIND_PACKAGE(Protobuf REQUIRED)

# add_subdirectory(project/lib/proto)
add_subdirectory(project/lib/ui)

add_executable(CloudSky_MyClient project/src/main.cpp)

target_link_libraries(CloudSky_MyClient Qt${QT_VERSION_MAJOR}::Widgets ui)

set_target_properties(CloudSky_MyClient PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

