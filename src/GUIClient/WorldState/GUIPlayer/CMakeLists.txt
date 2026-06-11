add_library(gui_player STATIC GUIPlayer.cpp)

target_include_directories(gui_player PUBLIC include)

target_link_libraries(gui_player PUBLIC warning_options)
