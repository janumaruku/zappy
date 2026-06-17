add_library(renderer Renderer.cpp
        ResourceManager.cpp
        include/ResourceManager.hpp
        Grid.cpp
        Grid.hpp)

target_include_directories(renderer PUBLIC include)

target_link_libraries(renderer PUBLIC utils warning_options zappy_data world_state raylib X11)
