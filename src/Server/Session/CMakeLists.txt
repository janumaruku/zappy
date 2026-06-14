add_library(zappy_server_session
  AClientSession.cpp
  AISession.cpp
  GUISession.cpp)
target_include_directories(zappy_server_session PUBLIC
  include
)
target_link_libraries(zappy_server_session PUBLIC
  network warning_options zappy_server_core_headers zappy_server_world_headers
)