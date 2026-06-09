/*
** EPITECH PROJECT, 2026
** NAME_OF_THE_PROJECT
** File description:
** No file there, just an Epitech Header example
*/

#include "Core.hpp"

#include "CommandBuilder.hpp"
#include "CommandContext.hpp"

namespace GUI {
Core::Core(int argc, char **argv): _argc(argc)
{
    for (auto i = 0; argv[i] != nullptr; i++)
        _argv.emplace_back(argv[i]);
}

void Core::run()
{
    buildGUICommands();

    _GUICommands.run(std::move(_argv));
}

void Core::buildGUICommands()
{
    _GUICommands =
        shell::command::CommandBuilder().name("./zappy_GUI")
        .description("Run the GUI client with the specified arguments.")
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("port").alias("p").required()
                .description("port linked to the server");
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("machine").alias("m").required()
                .description("hostname");
        })
        .action([](shell::command::CommandContext &ctx) {
            (void) ctx;
            // TCPClient t(_ioc, std::stoi(ctx.option("port")), ctx.option("machine"));
            //_tcpClient = ;
    }).build();
}
}
