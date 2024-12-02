// src/map.hpp
#pragma once
#include "raylib.h"
#include "planets.hpp"
#include <vector>
class Game;
struct PlanetInfo
{
    Planet planet;
    std::string name;
    Vector2 position;
    Texture2D texture;
    bool completed = false;
};

class Map
{
public:
    Map(Game *game);
    ~Map();
    void Update();
    void Draw();
    bool IsActive() const;
    Planet GetSelectedPlanet() const;
    void MarkPlanetCompleted(Planet planet);
    void Reset();
    Game *game;
    bool active = true;
    std::vector<PlanetInfo> planets;
    int selectedPlanetIndex = 0;
    std::vector<std::pair<int, int>> planetConnections;
};