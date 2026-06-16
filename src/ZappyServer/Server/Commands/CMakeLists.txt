add_library(zappy_server_commands STATIC
    BroadcastCommand.cpp
    ConnectNbrCommand.cpp
    EjectCommand.cpp
    ForkCommand.cpp
    ForwardCommand.cpp
    IncantationCommand.cpp
    InventoryCommand.cpp
    LeftCommand.cpp
    LookCommand.cpp
    RightCommand.cpp
    SetCommand.cpp
    TakeCommand.cpp
)
target_include_directories(zappy_server_commands PUBLIC
    include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
target_link_libraries(zappy_server_commands PUBLIC network world utils warning_options)