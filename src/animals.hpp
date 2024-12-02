// src/animal.hpp
#pragma once
#include "aliens.hpp"
#include "bullet.hpp"
#include <memory>
#include <vector>

class Animal : public Alien
{
public:
    int type;
    Animal(int type, Vector2 position, std::unique_ptr<Effect> effect);
    ~Animal();
    void Update(int direction) override;
    void Draw() override;
    Rectangle GetRectangle() override;

    static Texture2D animalImage[4];
};