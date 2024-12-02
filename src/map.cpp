// src/map.cpp
#include "map.hpp"
#include "raylib.h"
#include "game.hpp"

Map::Map(Game *game) : game(game)
{
    /*planets.push_back({Planet::Earth, {200, 300}});
    planets.push_back({Planet::Moon, {400, 200}});
    planets.push_back({Planet::Mars, {600, 350}});*/
    // Add more planets with their positions
    PlanetInfo earth;
    earth.planet = Planet::Earth;
    earth.name = "Earth";
    earth.position = {200, 300};
    earth.texture = LoadTexture("Graphics/earth.png");
    planets.push_back(earth);

    PlanetInfo moon;
    moon.planet = Planet::Moon;
    moon.name = "Moon";
    moon.position = {400, 300};
    moon.texture = LoadTexture("Graphics/moon.png");
    planets.push_back(moon);

    planetConnections.emplace_back(0, 1);
}
Map::~Map()
{
    for (auto &planetInfo : planets)
    {
        UnloadTexture(planetInfo.texture);
    }
}
Planet Map::GetSelectedPlanet() const
{
    return planets[selectedPlanetIndex].planet;
}
void Map::Update()
{
    if (IsKeyPressed(KEY_RIGHT))
    {
        selectedPlanetIndex = (selectedPlanetIndex + 1) % planets.size();
    }
    if (IsKeyPressed(KEY_LEFT))
    {
        if (selectedPlanetIndex == 0)
            selectedPlanetIndex = planets.size() - 1;
        else
            selectedPlanetIndex--;
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        active = false;
        Planet selectedPlanet = GetSelectedPlanet();
    }
}
// src/map.cpp
void Map::MarkPlanetCompleted(Planet planet)
{
    for (auto &planetInfo : planets)
    {
        if (planetInfo.planet == planet)
        {
            planetInfo.completed = true;
            break;
        }
    }
}

void Map::Reset()
{
    active = true;
    // Reset other necessary state variables if needed
}
void Map::Draw()
{

    DrawText("Select a Planet", 100, 50, 40, WHITE);

    /* for (size_t i = 0; i < planets.size(); ++i)
     {
         Colorl
        // Color color = (i == selectedPlanetIndex) ? YELLOW : WHITE;
         if (planets[i].completed)
         {
             color = GREEN;
         }
         DrawTextureV(planets[i].texture, planets[i].position, WHITE);

         DrawText(
             (planets[i].completed ? "Completed" : ""),
             planets[i].position.x - 30,
             planets[i].position.y + 30,
             20,
             color);
     }*/

    for (size_t i = 0; i < planets.size(); ++i)
    {
        // Determine the color based on selection and completion
        Color planetColor = WHITE; // Default color
        if (i == selectedPlanetIndex)
            planetColor = YELLOW; // Highlight selected planet
        if (planets[i].completed)
            planetColor = GREEN; // Completed planets in green

        // Draw the planet texture with the determined color
        DrawTextureV(planets[i].texture, planets[i].position, planetColor);
        int textWidth = MeasureText(planets[i].name.c_str(), 20);
        int textX = planets[i].position.x + (planets[i].texture.width / 2) - (textWidth / 2);
        int textY = planets[i].position.y + planets[i].texture.height + 10; // 10 pixels below the planet

        DrawText(planets[i].name.c_str(), textX, textY, 20, WHITE);
    }
}
bool Map::IsActive() const
{
    return active;
}