add_library(gui_protocol STATIC
        BctCommand.cpp
        EboCommand.cpp
        EdiCommand.cpp
        EnwCommand.cpp
        MctCommand.cpp
        MszCommand.cpp
        PicCommand.cpp
        PieCommand.cpp
        PnwCommand.cpp
        PpoCommand.cpp
        ProtocolHandler.cpp)


target_include_directories(gui_protocol PUBLIC include)

target_link_libraries(gui_protocol PUBLIC warning_options design_pattern world_state)
