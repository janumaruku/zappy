add_subdirectory(Commands)

add_library(server STATIC
    AClientSession.cpp
    AISession.cpp
    AIProtocolHandler.cpp
    GUISession.cpp
    GUIProtocolHandler.cpp
    Server.cpp
)
target_include_directories(server PUBLIC
    include
    Commands/include
)
target_link_libraries(server PUBLIC commands network world utils warning_options)