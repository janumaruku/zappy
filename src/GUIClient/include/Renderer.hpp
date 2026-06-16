/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Renderer
*/

#ifndef RENDERER_HPP
    #define RENDERER_HPP
    #include <string>
    #include <map>
    #include "raylib.h"

using PlayerId = int;
struct Texture2D_Dummy {};
struct Animation {};
struct WorldState {};
struct GUIMap {};
struct GUIPlayer {};
struct GUIEgg {};

class Renderer {
public:
    Renderer();
    ~Renderer();

    void loadTextures();
    void render(WorldState world);
    bool isWindowOpen() const;

private:
    void renderMap(GUIMap map);
    void renderPlayers(std::map<PlayerId, GUIPlayer> players);
    void renderEggs(std::map<unsigned int, GUIEgg> eggs);
    void updateAnimation(GUIPlayer player);

    std::map<std::string, Texture2D> _textures;
    std::map<PlayerId, Animation> _animations;
    Camera2D _camera;
};

#endif // RENDERER_HPP
