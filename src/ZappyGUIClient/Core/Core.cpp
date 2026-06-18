/*
** EPITECH PROJECT, 2026
** NAME_OF_THE_PROJECT
** File description:
** No file there, just an Epitech Header example
*/

#include "Core.hpp"

#include <memory>

#include "CommandBuilder.hpp"
#include "CommandContext.hpp"
#include "Renderer.hpp"

namespace zappy::gui {
Core::Core(char **argv)
{
    for (auto i = 0; argv[i] != nullptr; i++)
        _argv.emplace_back(argv[i]);
}

void Core::run()
{
    buildGUICommands();

    _guiCommands.run(std::move(_argv));
    const auto &map = _worldState.getMap();

    Renderer renderer(map.getWidth(), map.getHeight());
    while (renderer.isWindowOpen()) {
        renderer.render(_worldState);
    }
}

void Core::buildGUICommands()
{
    _guiCommands =
        shell::command::CommandBuilder()
        .name("./zappy_GUI")
        .description("Run the GUI client with the specified arguments.")
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("port")
                .alias("p")
                .required()
                .description("port linked to the server");
        })
        .option([](shell::command::OptionBuilder &builder) {
            builder.name("machine")
                .alias("m")
                .required()
                .description("hostname");
        })
        .action([this](const shell::command::CommandContext &ctx) {
            _tcpClient = std::make_unique<TCPClient>(_ioc,
                std::stoi(ctx.option("port")), ctx.option("machine"),
                _worldState);
        })
        .build();
}
} // namespace zappy::gui
