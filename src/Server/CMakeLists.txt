add_executable(zappy_server
  AClientSession.cpp
  AISession.cpp
  GUISession.cpp)

add_subdirectory(Core)


add_library(zappy_server)

target_include_directories(zappy_server PUBLIC
  include
)

target_link_libraries(zappy_server PUBLIC warning_options)

set_target_properties(zappy_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
