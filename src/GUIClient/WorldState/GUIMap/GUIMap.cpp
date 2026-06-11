/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIMap.cpp
*/

#include "GUIMap.hpp"

#include <string>

namespace zappy::gui {
GUIMap::GUIMap(uint width, uint height): _width(width), _height(height)
{

}

uint GUIMap::getWidth() const
{
    return _width;
}

uint GUIMap::getHeight() const
{
    return _height;
}

/*
 *Tile getTile(Position pos) {
 *
 *}
*/

/*void updateTile(Position pos, map<Ressource, uint> ressources) {
 *
 *}
 */
}
