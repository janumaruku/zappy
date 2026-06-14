/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Core.cpp
*/

#include "Core.hpp"

#include "CommandBuilder.hpp"
#include "CommandContext.hpp"
#include "Network.hpp"

Core::Core(char **argv)
{
    for (auto i = 0; argv[i] != nullptr; i++)
        _argv.emplace_back(argv[i]);
}

void Core::run()
{
    buildServerCommands();

<<<<<<< ZAP-5-Implement-Server-class-and-Acceptor
    shell::command::CommandContext context =
        _serverCommands.buildCommandContext(_argv);

    _serverCommands.handler(context);

    Server server(_port);
    server.run();
=======
    _serverCommands.run(std::move(_argv));
>>>>>>> dev
}

void Core::buildServerCommands()
{
    _serverCommands =
        shell::command::CommandBuilder().name("./zappy_server")
        .description("Runs the server with the specified arguments.")
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("port").alias("p").required()
                .description("port number.");
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("width").alias("x").required()
                .description("width of the world");
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("height").alias("y").required()
                .description("height of the world");
        })
        .xOption([](shell::command::XOptionBuilder &builder) {
            builder.name("name").alias("n").min(2).required()
                .description("name of the teams.");
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("clientsNb").alias("c").required()
                .description("number of initial client per team.");
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("frequency").alias("f").required()
                .description("reciprocal of time unit for execution of actions.");
        })
        .action([this](shell::command::CommandContext &ctx) {
            _port = std::stoi(ctx.option("port"));
            _width = std::stoi(ctx.option("width"));
            _height = std::stoi(ctx.option("height"));
            _teams = ctx.xOption("name");
            _clientPerTeam = std::stoi(ctx.option("clientsNb"));
            _frequency = std::stoi(ctx.option("frequency"));
        }).build();
}
