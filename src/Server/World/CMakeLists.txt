add_library(zappy_server_world_headers INTERFACE)
target_include_directories(zappy_server_world_headers INTERFACE include)

add_library(World
  Map.cpp
  Player.cpp)

target_include_directories(World PUBLIC include)
target_link_libraries(World PUBLIC warning_options)