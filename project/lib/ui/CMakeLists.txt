add_library(ui STATIC src/mainwindow.cpp include/mainwindow.h)

target_include_directories(ui PUBLIC include)

target_link_libraries(ui PUBLIC Qt5::Widgets) # MessageOperations
