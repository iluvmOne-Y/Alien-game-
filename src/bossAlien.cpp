#include "bossAlien.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <memory>

BossAlien::BossAlien(Vector2 position, std::unique_ptr<Effect> effect)
    : Alien(4, position, std::move(effect)),
      isDead(false),
      health(MAX_HEALTH),
      bulletType(std::make_unique<Boss_Bullet>()),
      lastShotTime((double)0.0)
{
    this->position.x = position.x - (alienImage[3].width) / 2.0f;
    this->position.y = position.y;
}

Rectangle BossAlien::GetRectangle()
{
    return Rectangle{
        position.x,
        position.y,
        static_cast<float>(alienImage[3].width),
        static_cast<float>(alienImage[3].height)};
}
void BossAlien::Shoot()
{
    bulletType->SHOOT(bossLasers, position.x, position.y, alienImage[3].width, lastShotTime);
}
void BossAlien::Update(int direction)
{
    // Custom boss movement pattern
    float time = GetTime();

    // Horizontal movement
    position.x += direction;

    // Keep boss within screen bounds
    float screenWidth = GetScreenWidth();
    float bossWidth = alienImage[3].width;

    if (position.x < 0)
    {
        position.x = 0;
    }
    if (position.x > screenWidth - bossWidth)
    {
        position.x = screenWidth - bossWidth;
    }
    if (GetTime() - lastShotTime > 1.0)
    {
        Shoot();
    }
    for (auto &laser : bossLasers)
    {
        laser.Update();
    }
    // Remove inactive lasers
    bossLasers.erase(std::remove_if(bossLasers.begin(), bossLasers.end(),
                                    [](Laser &l)
                                    { return !l.active; }),
                     bossLasers.end());
}

void BossAlien::Draw()
{
    if (isDead)
    {
        printf("BossAlien::Draw called - isDead: true\n"); // Debug statement
        if (Alien::alienImage[3].id != 0 && effect)
        {
            effect->ApplyEffect(WHITE, position, Alien::alienImage[3]);
            // tempor
            DrawCircleV(position, 10.0f, RED);
            printf("Static test circle drawn.\n");
        }
        else
        {
            printf("Error:Alien image or effect is null\n");
        }
    }
    else
    {

        Alien::Draw();
        // Draw larger alien with health bar
        DrawTextureV(alienImage[3], position, WHITE);

        float barWidth = alienImage[3].width;
        float barHeight = 10.0f;
        Vector2 barPos = {
            position.x,
            position.y - 20.0f};

        // Background (red)
        DrawRectangle(barPos.x, barPos.y, barWidth, barHeight, RED);

        // Current health (green)
        float currentWidth = (float)health / MAX_HEALTH * barWidth;
        DrawRectangle(barPos.x, barPos.y, currentWidth, barHeight, GREEN);
        for (auto &laser : bossLasers)
        {
            laser.Draw();
        }
    }
}
bool BossAlien::TakeDamage(int damage)
{
    if (isDead)
    {
        printf("BossAlien::TakeDamage called but boss is already dead.\n");
        return false;
    }
    health = health - damage;
    printf("BossAlien took %d damage. Health is now %d.\n", damage, health);
    if (health <= 0 && !isDead)
    {
        isDead = true;
        effect = std::make_unique<ExplodeEffect>();
        printf("BossAlien has died. Explosion effect initialized.\n");
        return true;
    }
    return false;
}
std::vector<Laser> &BossAlien::GetLasers()
{
    return bossLasers;
}
BossAlien::~BossAlien()
{
}