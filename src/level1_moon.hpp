#pragma once
#include "level.hpp"
#include "game.hpp"
class Level1_moon : public Level
{
public:
    Level1_moon() = default;
    std::shared_ptr<Level> Clone() const override
    {
        return std::make_shared<Level1_moon>();
    }
    void Load(Game &game) override
    {
        int alienRows = 3;
        int alienCols = 5;
        game.aliens = game.createAnimals(alienRows, alienCols);
        game.aliensDirection = 2;
    }
};