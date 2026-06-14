add_library(zappy_server
  AClientSession.cpp
  AISession.cpp
  GUISession.cpp)
add_subdirectory(Core)
target_include_directories(zappy_server PUBLIC
  include
)
target_link_libraries(zappy_server PUBLIC network warning_options)