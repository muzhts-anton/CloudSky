set(QT_PROJECT_SOURCES src/mainwindow.cpp)

add_library(ui STATIC ${QT_PROJECT_SOURCES})
target_include_directories(ui PUBLIC include)

target_link_libraries(ui Qt${QT_VERSION_MAJOR}::Widgets MessageOperations)
