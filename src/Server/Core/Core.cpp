/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Core.cpp
*/

#include "Core.hpp"

#include "CommandBuilder.hpp"
#include "CommandContext.hpp"

Core::Core(char **argv)
{
    for (auto i = 0; argv[i] != nullptr; i++)
        _argv.emplace_back(argv[i]);
}

void Core::run()
{
    buildServerCommands();
    shell::command::CommandContext context =
        _serverCommands.buildCommandContext(_argv);
    _serverCommands.handler(context);
}

void Core::buildServerCommands()
{
    _serverCommands =
        shell::command::CommandBuilder().name("./zappy_server")
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("help").alias("h");
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("port").alias("p").required();
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("width").alias("x").required();
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("height").alias("y").required();
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("name").alias("n").required();
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("clientsNb").alias("c").required();
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("frequency").alias("f").required();
        })
        .action([this](shell::command::CommandContext &ctx) {
            _port = std::stoi(ctx.option("port"));
            _width = std::stoi(ctx.option("width"));
            _height = std::stoi(ctx.option("height"));
            _teams.push_back(ctx.option("name"));
            _clientPerTeam = std::stoi(ctx.option("clientsNb"));
            _frequency = std::stoi(ctx.option("frequency"));
        }).build();
}
