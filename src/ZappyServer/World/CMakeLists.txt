add_library(world STATIC Map.cpp
        Player.cpp)

target_include_directories(world PUBLIC include)

target_link_libraries(world PUBLIC utils zappy_data warning_options)