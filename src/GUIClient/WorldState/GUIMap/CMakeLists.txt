add_library(gui_map STATIC GUIMap.cpp)

target_include_directories(gui_map PUBLIC include)

target_link_libraries(gui_map PUBLIC warning_options)
