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
#include "Animation.hpp"
#include "FactoryTemplate.hpp"
#include "Grid.hpp"
#include "Hud.hpp"
#include "HudManager.hpp"
#include "ZappyEvents.hpp"
#include "raylib.h"
#include "ResourceManager.hpp"
#include "WorldState.hpp"

namespace zappy::gui {
using SubjectList = std::initializer_list<std::pair<ZappyEventType,
    designPattern::ISubject<ZappyEvent, ZappyEventType> &>>;

constexpr float WINDOW_WIDTH = 800;
constexpr float WINDOW_HEIGHT = 600;

constexpr Color INCANTATION_COLOR = {.r=160, .g=32, .b=255, .a=100};
constexpr Color INCANTATION_FAILURE_COLOR = {.r=0, .g=255, .b=0, .a=100};
constexpr Color INCANTATION_SUCCESS_COLOR = {.r=255, .g=0, .b=0, .a=100};

constexpr Color GAMEOVER_BACKRGOUND_COLOR = {.r=0, .g=0, .b=0, .a=50};

constexpr std::chrono::milliseconds INCANTATION_END_DURATION = std::chrono::milliseconds(1000);

class Renderer: public designPattern::AObserver<ZappyEvent, ZappyEventType> {
public:
    Renderer(const int &width, const int &height, const SubjectList &list, const WorldState &worldState);

    ~Renderer() override;

    void render(const WorldState &world);

    bool isWindowOpen();

    void onNotify(const ZappyEvent &event) override;

private:

    void registerCreators();


    struct OnEvent {
        explicit OnEvent(Renderer &renderer): renderer{renderer} {}

        void operator()(const PlayerNewEvent &)
        {
        }

        void operator()(const PlayerMovedEvent &event)
        {
            const Animation animation(event.action, tileToPixel(event.position), renderer._animationManager->getTexture(PLAYER_MOVEMENT_NAME));

            renderer._animations.emplace(event.id, animation);
        }

        void operator()(const PlayerDiedEvent &event)
        {
            renderer._animations.erase(event.id);
        }

        void operator()(const PlayerInventoryAssignEvent &)
        {
        }

        void operator()(const PlayerBroadcastEvent &)
        {
        }

        void operator()(const TileUpdateEvent &)
        {
        }

        void operator()(const TimeUpdateEvent &)
        {
        }

        void operator()(const EggLaidEvent &event)
        {
            renderer._eggs.emplace(event.eggId, event.position);
        }

        void operator()(const EggHatchedEvent &event)
        {
            renderer._eggs.erase(event.egdId);
        }

        void operator()(const EggDiedEvent &event)
        {
            renderer._eggs.erase(event.egdId);
        }

        void operator()(const IncantationStartEvent &event)
        {
            renderer._incantations.emplace(event.position,
                std::chrono::steady_clock::now());
        }

        void operator()(const IncantationEndEvent &event)
        {
            renderer._incantations.erase(event.position);
            renderer._incantationsRes.emplace(event.position, std::make_pair(event.result, std::chrono::steady_clock::now()));
        }

        void operator()(const GameEndEvent &event)
        {
            renderer._winner = event.team;
        }

        Renderer &renderer;
    };

    void renderMap(const GUIMap &map);

    void renderResourcesFromTile(const std::unordered_map<data::Resource, int>& tile,
        data::Position position) const;

    void renderPlayers(const std::unordered_map<data::PlayerId, GUIPlayer>
            &players, const std::unordered_map<std::string, Team>& teams) const;

    void renderEggs();

    void renderIncantation(const data::Position position);

    void renderGameOver();

    static void updateAnimation(const GUIPlayer &player);

    void updateCamera();
    void updateZoom(const float &wheel);
    void updateCameraMovement();
    void updateHud(const WorldState& worldState);

    [[nodiscard]] static Vector2 tileToPixel(data::Position pos);

    static std::string resourceToString(const data::Resource &resource);
    static std::string playerOrientationToString(
        const data::Orientation &orientation);

    // std::map<data::PlayerId, Animation> _animations;
    Grid _grid;
    Camera2D _camera;
    HUD _hud;
    std::unique_ptr<HUDManager> _hudManager;
    std::unique_ptr<ResourceManager> _resourceManager;
    std::unique_ptr<AnimationManager> _animationManager;
    std::unordered_map<std::string, data::Position> _eggs;
    std::map<data::Position, std::chrono::steady_clock::time_point> _incantations;
    std::map<data::Position, std::pair<bool, std::chrono::steady_clock::time_point>> _incantationsRes;
    std::unordered_map<data::PlayerId, Animation> _animations;
    std::optional<std::string> _winner;

    //AnimationFactory _animationFactory;
};
} // namespace zappy::gui
#endif // RENDERER_HPP
