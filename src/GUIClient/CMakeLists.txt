add_subdirectory(WorldState)

add_executable(zappy_gui main.cpp)

target_include_directories(zappy_gui PUBLIC include)

target_link_libraries(zappy_gui PUBLIC shell warning_options world_state team)