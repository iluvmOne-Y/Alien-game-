#pragma once
#include <raylib.h>
#include <cmath>
#include <memory>
#include "effect.hpp"
using namespace std;

class Color_Effect;
class DeathEffect;

class Alien
{
public:
    Alien(int type, Vector2 position, std::unique_ptr<Effect> fx); /*, const shared_ptr<DeathEffect>& deffect*/
    virtual void Update(int direction);
    virtual int GetType();
    virtual void Draw();
    static void UnloadImage();
    static Texture2D alienImage[4];
    virtual Rectangle GetRectangle();

    int type;
    Vector2 position;
    std::unique_ptr<Effect> effect;
    Color baseColor;
};
