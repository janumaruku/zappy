/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "Map.hpp"
#include <stdexcept>
#include <iterator>
#include "constants.hpp"

namespace zappy::server {

Map::Map(const int width, const int height): _width(width), _height(height)
{
    auto len = width * height;

    auto i = 0;
    for (auto j = 0; j < len; ++j) {
        if (j == width - 1)
            ++i;

        _tiles.emplace_back(data::Position{j % width, i});
    }
    generate();
}

int Map::getWidth() const noexcept
{
    return this->_width;
}

int Map::getHeight() const noexcept
{
    return this->_height;
}

const data::Tile &Map::getTile(const data::Position &pos) const
{
    if (pos.getX() > _width || pos.getX() < 0 || pos.getY() > _height || pos.
        getY() < 0)
        throw std::out_of_range("Position out of map bounds");

    const std::size_t index = (pos.getY() * this->_width) + pos.getX();

    return _tiles[index];
}

const Player &Map::getPlayer(const PlayerId &id) const
{
    if (!_players.contains(id))
        throw std::out_of_range("No data found for key " + id);

    return _players.at(id);
}

Player &Map::getPlayer(const PlayerId &id)
{
    if (!_players.contains(id))
        throw std::out_of_range("No data found for key " + id);

    return _players.at(id);
}

const std::unordered_map<PlayerId, Player> &Map::getPlayers() const noexcept
{
    return _players;
}

bool Map::hasPlayer(const PlayerId &id) const noexcept
{
    return _players.contains(id);
}

Player &Map::spawnPlayer(const PlayerId &id, const TeamId &team)
{
    const data::Position position{
        utils::randomNumber(0, _width - 1),
        utils::randomNumber(0, _height - 1)
    };

    auto [it, inserted] = _players.emplace(id, Player{id, team, position, 1, _width, _height});
    if (!inserted)
        throw std::runtime_error("Player already exists: " + id);
    return it->second;
}

void Map::generate()
{
    static const uint food = static_cast<uint>(_width * _height * 0.5);
    static const uint linemate = static_cast<uint>(_width * _height * 0.3);
    static const uint deraumere = static_cast<uint>(_width * _height * 0.15);
    static const uint sibur = static_cast<uint>(_width * _height * 0.1);
    static const uint mendiane = static_cast<uint>(_width * _height * 0.1);
    static const uint phiras = static_cast<uint>(_width * _height * 0.08);
    static const uint thystame = static_cast<uint>(_width * _height * 0.05);

    generateResource(data::Resource::FOOD, food);
    generateResource(data::Resource::LINEMATE, linemate);
    generateResource(data::Resource::DERAUMERE, deraumere);
    generateResource(data::Resource::SIBUR, sibur);
    generateResource(data::Resource::MENDIANE, mendiane);
    generateResource(data::Resource::PHIRAS, phiras);
    generateResource(data::Resource::THYSTAME, thystame);
}

void Map::generateResource(const data::Resource &resource, const uint amount)
{
    for (auto i = 0UL; i < amount; ++i) {
        const auto x = utils::randomNumber(0, _width - 1);
        const auto y = utils::randomNumber(0, _height - 1);
        const auto index = (y * _width) + x;
        auto &tile = _tiles[index];
        tile.dropResource(resource);
    }
}

bool Map::takeResource(const data::Resource& resource, const data::Position& pos)
{
    if (pos.getX() > _width || pos.getX() < 0 || pos.getY() > _height || pos.
        getY() < 0)
        throw std::out_of_range("Position out of map bounds");

    const auto index = (pos.getY() * this->_width) + pos.getX();
    auto &tile = _tiles[index];

    if (tile.hasResource(resource))
        return false;

    tile.takeResource(resource);
    return true;
}

void Map::dropResource(const data::Resource &resource, const data::Position &pos)
{
    if (pos.getX() > _width || pos.getX() < 0 || pos.getY() > _height || pos.
        getY() < 0)
        throw std::out_of_range("Position out of map bounds");

    const auto index = (pos.getY() * this->_width) + pos.getX();
    auto &tile = _tiles[index];

    tile.dropResource(resource);
}
}
