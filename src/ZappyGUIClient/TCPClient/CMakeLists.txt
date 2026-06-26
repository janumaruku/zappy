add_library(tcp_client TCPClient.cpp)

target_include_directories(tcp_client PUBLIC include)

target_link_libraries(tcp_client PUBLIC zappy_data warning_options network gui_protocol world_state)
