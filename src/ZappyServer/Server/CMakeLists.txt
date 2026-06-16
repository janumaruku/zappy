add_library(server STATIC
    AClientSession.cpp
    AISession.cpp
    GUISession.cpp
    Server.cpp
)

add_subdirectory(Commands)

target_include_directories(server PUBLIC include)

target_link_libraries(server PUBLIC network world server_commands utils warning_options)
