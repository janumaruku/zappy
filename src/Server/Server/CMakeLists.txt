add_library(server STATIC
    AClientSession.cpp
    AISession.cpp
    GUISession.cpp
    Server.cpp
)

target_include_directories(server PUBLIC include)

target_link_libraries(server PUBLIC network world utils warning_options)
