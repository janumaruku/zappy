add_executable(zappy_gui main.cpp Renderer.cpp)

target_include_directories(zappy_gui PUBLIC include)

target_link_libraries(zappy_gui PUBLIC
    shell
    warning_options
    raylib
    GL
    m
    pthread
    dl
    rt
    X11
)

set_target_properties(zappy_gui PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
