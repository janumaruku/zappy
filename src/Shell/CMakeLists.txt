add_library(shell STATIC LineBuffer.cpp
        include/LineBuffer.hpp
        TerminalGuard.cpp
        include/TerminalGuard.hpp
        KeyDispatcher.cpp
        include/KeyDispatcher.hpp
        Prompt.cpp
        include/Prompt.hpp
        CommandContext.cpp
        CommandDefinition.cpp
        ContextException.cpp
        CommandBuilder.cpp
        include/CommandBuilder.hpp
        PositionalArgumentBuilder.cpp
        include/PositionalArgumentBuilder.hpp
        OptionBuilder.cpp
        include/OptionBuilder.hpp
        FlagBuilder.cpp
        include/FlagBuilder.hpp
        Shell.cpp
        include/Shell.hpp
        ShellException.cpp
        include/ShellException.hpp
        HelpFormatter.cpp
        include/HelpFormatter.hpp)

target_include_directories(shell PUBLIC include)

target_link_libraries(shell PUBLIC utils warning_options)
