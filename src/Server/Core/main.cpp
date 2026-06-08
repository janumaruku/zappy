/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** main
*/

#include <iostream>

#include "Core.hpp"

int main(int argc, char** argv)
{
    try {
        Core core(argc, argv);
        core.run();
    } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        return 84;
    }
}
