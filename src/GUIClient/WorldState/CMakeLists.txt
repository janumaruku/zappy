add_library(world_state WorldState.cpp)

add_subdirectory(GUIMap)

add_subdirectory(GUIPlayer)

add_subdirectory(Team)

add_subdirectory(GUIEgg)

target_include_directories(world_state PUBLIC include)

target_link_libraries(world_state PUBLIC warning_options gui_map gui_player gui_player gui_egg team)

