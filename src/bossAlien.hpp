// In boss_alien.hpp
#pragma once
#include "aliens.hpp"
#include "bullet.hpp"
#include <memory>
#include <vector>

class BossAlien : public Alien
{
private:
    int health; // can be healed with a little help from a npc class, which will also have the health of 5, and also can heal itself, let say it can heal after 0.5 period of second, which
    std::vector<Laser> bossLasers;
    std::unique_ptr<Bullet_Type> bulletType;
    double lastShotTime;

public:
    BossAlien(Vector2 position, std::unique_ptr<Effect> effect);
    ~BossAlien();
    void Update(int direction) override;
    void Draw() override;
    Rectangle GetRectangle() override;
    static void UnloadImage();
    std::vector<Laser> &GetLasers();
    bool TakeDamage(int damage);
    int GetHealth() const { return health; }
    void Shoot();
    static const int MAX_HEALTH = 30;
    static constexpr float DAMAGE_FLASH_TIME = 0.1f;
    bool isDead;
};

// In boss_alien.cpp
