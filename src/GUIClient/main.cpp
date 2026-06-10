/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** main
*/

#include <iostream>

#include "WorldState.hpp"
#include "../Shell/include/CommandBuilder.hpp"
#include "../Shell/include/CommandContext.hpp"
#include "WorldState/Team/include/Team.hpp"

int main()
{
    zappy::gui::WorldState worldStateTest;
    zappy::gui::Team TeamTest("testName", "TestColor");
    auto command = shell::command::CommandBuilder{}.name("test")
        .description("Test command")
        .xOption([](auto &builder) {
            builder.name("xoption").alias("o").min(2).required();
        })
        .action([](shell::command::CommandContext &context) {
            const auto options = context.xOption("xoption");

            for (const auto &opt: options)
                std::clog << opt << std::endl;
        }).build();

    command.run({"test", "-h"/*, "one", "two"*/});
    return 0;
}
