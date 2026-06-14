add_executable(zappy_gui Core.cpp main.cpp)

target_include_directories(zappy_gui PUBLIC include)

target_link_libraries(zappy_gui PUBLIC warning_options shell network world_state tcp_client)

set_target_properties(zappy_gui PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
