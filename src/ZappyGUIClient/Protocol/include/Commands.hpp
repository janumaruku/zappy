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
class MctCommand: public GUICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) override;

    bool operator()(WorldState &worldState,
    const std::vector<std::string> &args) override;

    static std::unique_ptr<GUICommand> create();
};

class BctCommand: GUICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getBct() const;
};

class TnaCommand: GUICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getTna() const;
};

class PpoCommand: GUICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getPpo() const;
};

class PlvCommand: GUICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getPlv() const;
};
/*
class PinCommand: GUICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getPin() const;
};

class SgtCommand: GUICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getSgt() const;
};

class SstCommand: GUICommand {
public:
    bool execute(WorldState &worldState,
        const std::vector<std::string> &args) = 0;

    bool getSst() const;
};
*/
}
#endif
