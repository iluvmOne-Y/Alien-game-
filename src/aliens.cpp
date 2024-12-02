#include "aliens.hpp"

Texture2D Alien::alienImage[4] = {};

Alien::Alien(int type, Vector2 position, std::unique_ptr<Effect> fx /*,const shared_ptr<DeathEffect>& deffect*/)
{
    this->type = type;
    this->position = position;
    this->effect = std::move(fx);
    // this->onShotEffect = deffect;

    if (alienImage[type - 1].id == 0)
    {

        switch (type)
        {
        case 1:
            alienImage[0] = LoadTexture("Graphics/alien_1.png");
            break;
        case 2:

            alienImage[1] = LoadTexture("Graphics/alien_2.png");
            break;
        case 3:
            alienImage[2] = LoadTexture("Graphics/alien_3.png");
            break;
        case 4:
            alienImage[3] = LoadTexture("Graphics/boss.png");
            break;
        default:
            alienImage[0] = LoadTexture("Graphics/alien_1.png");
            break;
        }
    }
}
void Alien::Draw()
{
    Color tint = baseColor;
    if (effect)
    {
        tint = effect->ApplyEffect(baseColor, position, alienImage[type - 1]);
    }
    DrawTextureV(alienImage[type - 1], position, tint);
}

void Alien::UnloadImage()
{
    for (int i = 0; i < 4; i++)
    {
        UnloadTexture(alienImage[i]);
    }
}
Rectangle Alien::GetRectangle()
{
    return {position.x, position.y, (float)alienImage[type - 1].width, (float)alienImage[type - 1].height};
}
int Alien::GetType()
{
    return type;
}
void Alien::Update(int direction)
{
    position.x += direction;
}