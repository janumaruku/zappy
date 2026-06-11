add_library(tile Tile.cpp)

target_include_directories(tile PUBLIC include)

target_link_libraries(tile PUBLIC warning_options position)