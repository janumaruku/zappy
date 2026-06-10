add_library(world_state WorldState.cpp)

add_subdirectory(GUIMap)

#add_subdirectory(GUIPlayer)

add_subdirectory(Team)

target_include_directories(world_state PUBLIC include)

target_link_libraries(world_state PUBLIC shell warning_options gui_map)

#set_target_properties(zappy_gui PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
