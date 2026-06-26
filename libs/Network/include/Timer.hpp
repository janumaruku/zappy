/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** Timer.hpp
*/

#pragma once
#include <chrono>
#include "BasicWaitableTimer.hpp"

using SteadyTimer = network::BasicWaitableTimer<std::chrono::steady_clock>;
using SystemTimer = network::BasicWaitableTimer<std::chrono::system_clock>;
using HighResolutionTimer = network::BasicWaitableTimer<std::chrono::high_resolution_clock>;