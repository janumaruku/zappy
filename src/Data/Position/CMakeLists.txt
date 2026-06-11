add_library(zappy_data Position.cpp)

target_include_directories(zappy_data PUBLIC include)

target_link_libraries(zappy_data PUBLIC warning_options)