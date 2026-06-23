# src/ZappyServer/Server/Commands/CMakeLists.txt
add_library(commands STATIC
    BroadcastCommand.cpp
    ConnectNbrCommand.cpp
    EjectCommand.cpp
    ForkCommand.cpp
    ForwardCommand.cpp
    IncantationCommand.cpp
    InventoryCommand.cpp
    MszCommand.cpp
    LeftCommand.cpp
    LookCommand.cpp
    PinCommand.cpp
    PnwCommand.cpp
    PpoCommand.cpp
    RightCommand.cpp
    SetCommand.cpp
    TakeCommand.cpp
    TnaCommand.cpp
)

target_include_directories(commands PUBLIC
    include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
target_link_libraries(commands PUBLIC world network utils)