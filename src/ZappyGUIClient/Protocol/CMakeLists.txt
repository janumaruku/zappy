add_library(gui_protocol STATIC
        BctCommand.cpp
        EboCommand.cpp
        EdiCommand.cpp
        EnwCommand.cpp
        MctCommand.cpp
        MszCommand.cpp
        PbcCommand.cpp
        PdiCommand.cpp
        PdrCommand.cpp
        PexCommand.cpp
        PfkCommand.cpp
        PgtCommand.cpp
        PicCommand.cpp
        PieCommand.cpp
        PinCommand.cpp
        PlvCommand.cpp
        PnwCommand.cpp
        PpoCommand.cpp
        SegCommand.cpp
        SgtCommand.cpp
        SmgCommand.cpp
        SstCommand.cpp
        TnaCommand.cpp
        ProtocolHandler.cpp)


target_include_directories(gui_protocol PUBLIC include)

target_link_libraries(gui_protocol PUBLIC warning_options design_pattern world_state)
