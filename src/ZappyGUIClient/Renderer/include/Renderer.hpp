/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Renderer.hpp
*/

#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <map>
#include <memory>
#include <string>

#include "AObserver.hpp"
#include "Grid.hpp"
#include "raylib.h"
#include "ResourceManager.hpp"
#include "WorldState.hpp"

namespace zappy::gui {
using SubjectList = std::initializer_list<std::pair<ZappyEventType,
    designPattern::ISubject<ZappyEvent, ZappyEventType> &>>;

constexpr float WINDOW_WIDTH = 800;
constexpr float WINDOW_HEIGHT = 600;

class Renderer: public designPattern::AObserver<ZappyEvent, ZappyEventType> {
public:
    Renderer(const int &width, const int &height, const SubjectList &list);

    ~Renderer() override;

    void render(const WorldState &world);

    bool isWindowOpen();

    void onNotify(const ZappyEvent &event) override;

private:
    struct OnEvent {
        explicit OnEvent(Renderer &renderer_): renderer{renderer_} {}

        void operator()(const PlayerNewEvent &/*event*/)
        {
        }

        void operator()(const PlayerMovedEvent &/*event*/)
        {
        }

        void operator()(const PlayerDiedEvent &/*event*/)
        {
        }

        void operator()(const TileUpdateEvent &/*event*/)
        {
        }

        void operator()(const EggLaidEvent &/*event*/)
        {
        }

        void operator()(const EggHatchedEvent &/*event*/)
        {
        }

        void operator()(const EggDiedEvent &/*event*/)
        {
        }

        void operator()(const IncantationStartEvent &/*event*/)
        {
        }

        void operator()(const IncantationEndEvent &/*event*/)
        {
        }

        void operator()(const GameEndEvent &/*event*/)
        {
        }

        Renderer &renderer;
    };

    void renderMap(const GUIMap &map) const;

    void renderResourcesFromTile(const std::unordered_map<data::Resource, int>& tile,
        data::Position position) const;

    void renderPlayers(const std::unordered_map<data::PlayerId, GUIPlayer>
            &players, const std::unordered_map<std::string, Team>& teams) const;

    static void renderEggs(const std::map<unsigned int, data::Egg> &eggs);

    static void updateAnimation(const GUIPlayer &player);

    void updateCamera();
    void updateZoom(const float &wheel);
    void updateCameraMovement();

    [[nodiscard]] static Vector2 tileToPixel(data::Position pos);

    static std::string resourceToString(const data::Resource &resource);
    static std::string playerOrientationToString(
        const data::Orientation &orientation);

    // std::map<data::PlayerId, Animation> _animations;
    Grid _grid;
    Camera2D _camera;
    std::unique_ptr<ResourceManager> _resourceManager;
};
} // namespace zappy::gui
#endif // RENDERER_HPP
