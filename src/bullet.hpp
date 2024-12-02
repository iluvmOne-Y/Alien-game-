#pragma once

#include "lasers.hpp"
using namespace std;

class Bullet_Type
{
public:
    virtual void SHOOT(vector<Laser> &laz, float x, float y, float w, double &timefire) = 0;
    virtual ~Bullet_Type() = default;
};

class Normal_B : public Bullet_Type
{
public:
    void SHOOT(vector<Laser> &vec, float x, float y, float w, double &timefire) override
    {
        vec.push_back(Laser({x + (w / 2) - 2, y}, -6, 0, YELLOW));
        timefire = GetTime();
    }
};

class Long_B : public Bullet_Type
{
public:
    void SHOOT(vector<Laser> &vec, float x, float y, float w, double &timefire) override
    {
        vec.push_back(Laser({x + (w / 2) - 2, y}, -10, 0, RED));
        vec.push_back(Laser({x + (w / 2) - 2, y + 15}, -10, 0, RED));
        vec.push_back(Laser({x + (w / 2) - 2, y + 30}, -10, 0, RED));
        vec.push_back(Laser({x + (w / 2) - 2, y + 45}, -10, 0, RED));
        vec.push_back(Laser({x + (w / 2) - 2, y + 45}, -10, 0, RED));
        timefire = GetTime() + 1.05;
    }
};

class Span_B : public Bullet_Type
{
public:
    void SHOOT(vector<Laser> &vec, float x, float y, float w, double &timefire) override
    {
        vec.push_back(Laser({x + (w / 2) - 2, y}, -6, 0, BLUE));
        vec.push_back(Laser({x + (w / 2) - 2, y}, -6, 2, BLUE));
        vec.push_back(Laser({x + (w / 2) - 2, y}, -6, -2, BLUE));
        timefire = GetTime() + 0.3;
    }
};

class watermelon_B : public Bullet_Type
{
public:
    void SHOOT(vector<Laser> &vec, float x, float y, float w, double &timefire) override
    {
        int side = GetRandomValue(0, 2) - 1;
        int speed_x = GetRandomValue(1, 7);
        vec.push_back(Laser({x + (w / 2) - 2, y}, -6, side * speed_x, WHITE));
        timefire = GetTime() - 0.05;
    }
};
class Boss_Bullet : public Bullet_Type
{
public:
    void SHOOT(std::vector<Laser> &vec, float x, float y, float w, double &timefire) override
    {
        vec.push_back(Laser({x + (w / 2) - 2, y}, 6, 0, PURPLE));
        vec.push_back(Laser({x + (w / 2) - 12, y + 15}, 6, -2, PURPLE));
        vec.push_back(Laser({x + (w / 2) + 8, y + 15}, 6, 2, PURPLE));
        timefire = GetTime();
    }
};
