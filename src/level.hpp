#pragma once
#include <memory>
class Game;
class Level
{
public:
    virtual ~Level() = default;
    virtual std::shared_ptr<Level> Clone() const = 0;
    virtual void Load(Game &game) = 0;
};
