#pragma once

#include <memory>
#include "bullet.hpp"
using namespace std;

class Spaceship
{
public:
  void setBulletType(const shared_ptr<Bullet_Type> &bullet);
  Spaceship();
  ~Spaceship();
  void Draw();
  void MoveLeft();
  void MoveRight();
  void FireLaser();
  void changeGun();
  Rectangle GetRectangle();
  void Reset();
  std::vector<Laser> lasers;
  Vector2 position;
  static const int MAX_HEALTH = 200;
  int GetHealth() const;
  void TakeDamage(int damage);
  int speed;
  int health;

private:
  Texture2D image;
  int guntype;

  // strategies
  shared_ptr<Bullet_Type> B_T;

  double timeFire;
};
