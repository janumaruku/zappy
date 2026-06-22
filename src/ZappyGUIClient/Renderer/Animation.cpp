/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** Animation.cpp
*/

#include "Animation.hpp"
#include <chrono>
#include <memory>
#include <raylib.h>
#include "GUIPlayer.hpp"

namespace zappy::gui {

Animation::Animation(Vector2 pos, Texture2D &sheet):
_spriteSheet(sheet),
_frameInfo{.width = sheet.height,
            .height       = sheet.height,
            .count        = sheet.width / sheet.height,
            .currentFrame = 0,
            .duration     = 0.1F},

_animStart(std::chrono::high_resolution_clock::now()),
_frameStart(std::chrono::high_resolution_clock::now()), _startPos(pos),
_currentPos(pos), _endPos(pos),
_duration((static_cast<float>(sheet.width) /
              static_cast<float>(sheet.height)) *
    0.1F),
_frameCount(sheet.width / sheet.height)
{}


void Animation::update()
{
    using Clock = std::chrono::high_resolution_clock;
    using Fsec  = std::chrono::duration<float>;

    const auto now = Clock::now();

    // Frame advancement
    const float frameElapsed = std::chrono::duration_cast<Fsec>(now - _frameStart).count();

    if (frameElapsed >= _frameInfo.duration) {
        _frameInfo.currentFrame = (_frameInfo.currentFrame + 1) % _frameCount;
        _frameStart   = now;
    }

    // Position interpolation 
    const float totalElapsed = std::chrono::duration_cast<Fsec>(now - _animStart).count();
    const float t = std::clamp(totalElapsed / _duration, 0.0F, 1.0F);

    _currentPos = {
        .x = _startPos.x + (t * (_endPos.x - _startPos.x)),
        .y = _startPos.y + (t * (_endPos.y - _startPos.y)),
    };
}

const Vector2 &Animation::currentPosition() const
{
    return _currentPos;
}

Rectangle Animation::currentSourceRect() const
{
    const long col = _frameInfo.currentFrame % (_spriteSheet.width / _frameInfo.width);
    const long row = _frameInfo.currentFrame / (_spriteSheet.width / _frameInfo.width);

    return Rectangle {
        .x      = static_cast<float>(col * _frameInfo.width),
        .y      = static_cast<float>(row * _frameInfo.height),
        .width  = static_cast<float>(_frameInfo.width),
        .height = static_cast<float>(_frameInfo.height),
    };
}

const Texture2D &Animation::getSpriteSheet() const
{
    return _spriteSheet;
}

bool Animation::isFinished() const
{
    return (static_cast<float>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) -
    static_cast<float>(_animStart.time_since_epoch().count())) >= _duration;
}

std::unique_ptr<Animation> Animation::create(/*Action a, */Vector2 pos, Texture2D &sheet)
{
    return std::make_unique<Animation>(/*a, */pos, sheet);
}

}