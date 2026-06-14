add_library(zappy_data STATIC Position.cpp
        Egg.cpp
        Tile.cpp)

target_include_directories(zappy_data PUBLIC include)

target_link_libraries(zappy_data PUBLIC warning_options)
