add_library(renderer STATIC
        Renderer.cpp
        ResourceManager.cpp
        Grid.cpp
        Hud.cpp
        HudManager.cpp
        Animation.cpp
        AnimationManager.cpp)

target_include_directories(renderer PUBLIC include)

target_link_libraries(renderer PUBLIC utils warning_options zappy_data world_state raylib X11)
