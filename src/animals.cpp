// src/animal.cpp
#include "animals.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <memory>

Texture2D Animal::animalImage[4] = {};

Animal::Animal(int type, Vector2 position, std::unique_ptr<Effect> effect)
    : Alien(5, position, std::move(effect)) // Use a unique type identifier

{
    this->type = type;
    if (animalImage[type - 1].id == 0)
    {

        switch (type)
        {
        case 1:
            animalImage[0] = LoadTexture("Graphics/cat1.png");
            break;
        case 2:

            animalImage[1] = LoadTexture("Graphics/cat2.png");
            break;
        case 3:
            animalImage[2] = LoadTexture("Graphics/dog.png");
            break;
        case 4:
            animalImage[3] = LoadTexture("Graphics/boss.png");
            break;
        default:
            animalImage[0] = LoadTexture("Graphics/cat1.png");
            break;
        }
    }
}

Rectangle Animal::GetRectangle()
{
    return Rectangle{
        position.x,
        position.y,
        static_cast<float>(animalImage[type - 1].width),
        static_cast<float>(animalImage[type - 1].height)};
}

void Animal::Update(int direction)
{
    position.x += direction;
    // Add any animal-specific behavior here
}

void Animal::Draw()
{

    DrawTextureV(animalImage[type - 1], position, WHITE);
}

Animal::~Animal()
{
    // Cleanup if necessary
}