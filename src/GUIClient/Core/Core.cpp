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
Core::Core(int argc, char **argv) : _argc(argc)
{
    for (auto i = 0; argv[i] != nullptr; i++)
        _argv.emplace_back(argv[i]);
}

void Core::run()
{
    buildGUICommands();
    shell::command::CommandContext context =
            _GUICommands.buildCommandContext(_argv);
    _GUICommands.handler(context);
}

void Core::buildGUICommands()
{
    _GUICommands =
        shell::command::CommandBuilder().name("./zappy_GUI")
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("help").alias("hp");
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("port").alias("p").required();
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("machine").alias("h").required();
        })
        .action([this](shell::command::CommandContext &ctx) {
            _port = std::stoi(ctx.option("port"));
            _machine = ctx.option("machine");
        }).build();
}
}
