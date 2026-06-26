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
    const uint food = static_cast<uint>(_width * _height * 0.5);
    const uint linemate = static_cast<uint>(_width * _height * 0.3);
    const uint deraumere = static_cast<uint>(_width * _height * 0.15);
    const uint sibur = static_cast<uint>(_width * _height * 0.1);
    const uint mendiane = static_cast<uint>(_width * _height * 0.1);
    const uint phiras = static_cast<uint>(_width * _height * 0.08);
    const uint thystame = static_cast<uint>(_width * _height * 0.05);

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
    const size_t currentAmount = getResourceCount(resource);

    if (currentAmount >= amount) {
        return;
    }

    const size_t amountToSpawn = amount - currentAmount;

    for (auto i = 0UL; i < amountToSpawn; ++i) {
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

    if (!tile.hasResource(resource))
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

void Map::addEgg(const data::Egg &egg)
{
    const uint id = _nextEggId++;
    data::Egg storedEgg(std::to_string(id),
        egg.getPlayerId(), egg.getTeam(), egg.getPosition(), egg.getLevel());
    _eggs.emplace(id, std::move(storedEgg));
}

void Map::removeEgg(const uint &eggId)
{
    _eggs.erase(eggId);
}

const std::unordered_map<uint, data::Egg> &Map::getEggs() const noexcept
{
    return _eggs;
}

std::unique_ptr<std::vector<uint>> Map::getEggsOnTile(const data::Position &pos) const
{
    std::vector<uint> out;

    for (const auto &kv : _eggs) {
        const auto &e = kv.second;
        if (e.getPosition().getX() == pos.getX() &&
            e.getPosition().getY() == pos.getY())
            out.push_back(kv.first);
    }
    return std::make_unique<std::vector<uint>>(out);
}

size_t Map::getResourceCount(const data::Resource &resource) const
{
    size_t count = 0;

    for (const auto &tile : _tiles) {
        const auto &resources = tile.getResources();
        const auto it = resources.find(resource);
        
        if (it != resources.end()) {
            if (it->second > 0) {
                count += static_cast<size_t>(it->second);
            }
        }
    }
    return count;
}
}
