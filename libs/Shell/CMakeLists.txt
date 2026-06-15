add_library(shell STATIC LineBuffer.cpp
        TerminalGuard.cpp
        KeyDispatcher.cpp
        Prompt.cpp
        CommandContext.cpp
        CommandDefinition.cpp
        ContextException.cpp
        CommandBuilder.cpp
        PositionalArgumentBuilder.cpp
        OptionBuilder.cpp
        FlagBuilder.cpp
        Shell.cpp
        ShellException.cpp
        HelpFormatter.cpp
        XOptionBuilder.cpp)

target_include_directories(shell PUBLIC include)

target_link_libraries(shell PUBLIC utils warning_options)
