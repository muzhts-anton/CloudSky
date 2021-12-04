set(UI_SRC
src/mainwindow.cpp
src/baseFragment.cpp
src/gameFragment.cpp
src/navigator.cpp
src/screensFactory.cpp
src/startFragment.cpp
)

set(UI_HDR
include/mainwindow.h
include/baseFragment.h
include/baseScreensFactory.h
include/gameFragment.h
include/navigator.h
include/screensFactory.h
include/screenNames.h
include/startFragment.h
)

add_library(ui STATIC ${UI_SRC} ${UI_HDR})

target_include_directories(ui PUBLIC include)

target_link_libraries(ui PUBLIC Qt5::Widgets) # MessageOperations
