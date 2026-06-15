add_library(gui_protocol STATIC ProtocolHandler.cpp Commands.cpp)

target_include_directories(gui_protocol PUBLIC include)

target_link_libraries(gui_protocol PUBLIC warning_options design_pattern world_state )
