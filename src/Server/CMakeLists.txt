add_executable(zappy_server
  main.cpp
  AClientSession.cpp
  AISession.cpp
  GUISession.cpp)

add_subdirectory(Core)


#add_library(server)
#
#target_include_directories(server PUBLIC include)
#
#target_link_libraries(server PUBLIC warning_options)
#
#set_target_properties(server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
