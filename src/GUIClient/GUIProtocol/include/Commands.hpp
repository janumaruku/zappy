/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Commands
*/

#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <functional>

#include "ProtocolHandler.hpp"
#include "WorldState.hpp"

namespace zappy::gui {

class MszCommand: public GUICommand {
public:
    ~MszCommand() override = default;

    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) override;

    bool operator()(WorldState &worldState,
        const std::vector<std::string> &args) override;

    static std::unique_ptr<GUICommand> create();
};

/*
class MctCommand: designPattern::ICommand<> {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) override;

    bool getMct() const;
};

class BctCommand: designPattern::ICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getBct() const;
};

class TnaCommand: designPattern::ICommand<> {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getTna() const;
};

class PpoCommand: designPattern::ICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getPpo() const;
};

class PlvCommand: designPattern::ICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getPlv() const;
};

class PinCommand: designPattern::ICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getPin() const;
};

class SgtCommand: designPattern::ICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getSgt() const;
};

class SstCommand: designPattern::ICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getSst() const;
};
*/
}
#endif
