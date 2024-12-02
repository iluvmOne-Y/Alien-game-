#include "lasers.hpp"

Laser::Laser(Vector2 position, int speed, int x_speed, Color color)
{
  this->position = position;
  this->speed = speed;
  this->speed_x = x_speed;
  active = true;
  this->color = color;
}

void Laser::Draw()
{
  if (active)
  {
    DrawRectangle(position.x, position.y, 4, 15, this->color);
  }
}
void Laser::Update()
{
  position.y += speed;
  position.x += speed_x;
  if (position.y > GetScreenHeight() || position.y < 0)
  {
    active = false;
  }
}

Rectangle Laser::GetRectangle()
{
  Rectangle rect;
  rect.x = position.x;
  rect.y = position.y;
  rect.width = 4;
  rect.height = 15;
  return rect;
}