add_library(gui_egg STATIC GUIEgg.cpp)

target_include_directories(gui_egg PUBLIC include)

target_link_libraries(gui_egg PUBLIC warning_options)
