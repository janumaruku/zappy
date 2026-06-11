/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** main
*/

#include <iostream>

#include "GUIEgg.hpp"
#include "WorldState.hpp"
#include "../Shell/include/CommandBuilder.hpp"
#include "../Shell/include/CommandContext.hpp"
#include "WorldState/GUIPlayer/include/GUIPlayer.hpp"
#include "WorldState/Team/include/Team.hpp"

int main()
{
    //zappy::gui::WorldState worldStateTest;
    zappy::gui::Team TeamTest("testName");
    zappy::gui::GUIPlayer GUIPlayerTest("testId", "testTeam",
        zappy::gui::Orientation::NORTH, 0);
    zappy::gui::GUIEgg eggTest(0, "testId", {0, 0});
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
