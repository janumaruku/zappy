/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIMap.hpp
*/

#ifndef GUIMAP_HPP
#define GUIMAP_HPP
#include <sys/types.h>

namespace zappy::gui {
class GUIMap {
public:
    uint getWidth() const;

    uint getHeight() const;

    //Tile getTile(Position pos);
    //void updateTile(Position pos, map<Ressource, uint> ressources);
private:
    uint _width = 0;
    uint _height = 0;
    //list<Tile> _tiles;
};
}

#endif
