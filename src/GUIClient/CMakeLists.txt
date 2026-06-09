cmake_minimum_required(VERSION 4.2)

add_executable(zappy_gui main.cpp
        include/ProtocolHandler.hpp
        include/ICommand.hpp
        include/Commands.hpp
        ProtocolHandler.cpp
        Renderer.cpp)

target_include_directories(zappy_gui PUBLIC include)

target_link_libraries(zappy_gui PUBLIC shell warning_options)

set_target_properties(zappy_gui PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
