#pragma once
#include "level.hpp"
#include "game.hpp"
class Level3_moon : public Level
{
public:
    Level3_moon() = default;
    std::shared_ptr<Level> Clone() const override
    {
        return std::make_shared<Level3_moon>();
    }
    void Load(Game &game) override
    {
        game.aliens = game.createBoss();
    }
};
