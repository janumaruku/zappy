add_executable(zappy_gui WorldState.cpp)

add_subdirectory(GUIMap)

target_include_directories(zappy_gui PUBLIC include)

target_link_libraries(zappy_gui PUBLIC shell warning_options gui_map)

#set_target_properties(zappy_gui PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
