/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** Animation.hpp
*/

#pragma once

#include <chrono>
#include <raylib.h>
#include "GUIPlayer.hpp"


namespace zappy::gui {
struct FrameInfo {
    int width;
    int height;
    int count;
    long currentFrame;
    float duration;
};

class Animation {
public:
    Animation() = delete;
    ~Animation() = default;

    Animation(/*Action action, */Vector2 pos, Texture2D &sheet);

    void update();

    [[nodiscard]] const Vector2 &currentPosition() const;
    [[nodiscard]] Rectangle currentSourceRect() const;

    [[nodiscard]] const Texture2D &getSpriteSheet() const;
    
    [[nodiscard]] bool isFinished() const;

    static std::unique_ptr<Animation> create(/*Action a, */Vector2 pos, Texture2D &sheet);
private:
    Texture2D &_spriteSheet;
    FrameInfo _frameInfo;
    std::chrono::time_point<std::chrono::high_resolution_clock> _animStart;
    std::chrono::time_point<std::chrono::high_resolution_clock> _frameStart;
    Vector2 _startPos;
    Vector2 _currentPos;
    Vector2 _endPos;
    float _duration;
    
    //Action _action;

    uint _frameCount;
};
}