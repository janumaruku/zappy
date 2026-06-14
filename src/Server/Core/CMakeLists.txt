add_executable(server_core
  Core.cpp
  main.cpp)
target_include_directories(server_core PUBLIC include)
target_link_libraries(server_core PUBLIC warning_options shell zappy_server_session)
set_target_properties(server_core PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_NAME zappy_server)