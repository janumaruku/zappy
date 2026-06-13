add_library(World STATIC Map.cpp
        Player.cpp)

target_include_directories(World PUBLIC include)

target_link_libraries(World PUBLIC utils warning_options)