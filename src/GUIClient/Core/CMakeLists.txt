add_executable(zappy_gui main.cpp Core.cpp)

target_include_directories(zappy_gui PUBLIC include)

target_link_libraries(zappy_gui PUBLIC warning_options shell)

set_target_properties(zappy_gui PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
