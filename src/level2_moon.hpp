#pragma once
#include "level.hpp"
#include "game.hpp"
class Level2_moon : public Level
{
public:
    Level2_moon() = default;
    std::shared_ptr<Level> Clone() const override
    {
        return std::make_shared<Level2_moon>();
    }
    void Load(Game &game) override
    {
        int alienRows = 4;
        int alienCols = 7;
        game.aliens = game.createAnimals(alienRows, alienCols);
        game.aliensDirection = 3; // Faster movement
    }
};