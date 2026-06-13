add_executable(zappy_gui main.cpp)

target_include_directories(zappy_gui PUBLIC include)

target_link_libraries(zappy_gui PUBLIC shell warning_options world_state team gui_player gui_egg)

add_subdirectory(WorldState)

add_subdirectory(TCPClient)

set_target_properties(zappy_gui PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
