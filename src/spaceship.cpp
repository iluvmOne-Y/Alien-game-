#include "spaceship.hpp"
using namespace std;

Spaceship::Spaceship()
{

  image = LoadTexture("Graphics/spaceship.png");
  // float margin = 40.0f;
  // float screenWidth = GetScreenWidth() - (2 * margin);
  // float screenHeight = GetScreenHeight() - (2 * margin);

  // // Initialize spaceship position at bottom center of screen
  // float spaceshipX = margin + screenWidth / 2.0f - 32; // 32 is half the spaceship width
  // float spaceshipY = GetScreenHeight() - margin - 60;

  position.x = (GetScreenWidth() - image.width) / 2;
  position.y = GetScreenHeight() - image.height - 100;
  timeFire = 0.0;
  guntype = 0;
  health = MAX_HEALTH;
  speed = 5;
  setBulletType(make_shared<Normal_B>()); // set as default bullet type
}

Spaceship::~Spaceship() { UnloadTexture(image); }

void Spaceship::Draw() { DrawTextureV(image, position, WHITE); }

void Spaceship::setBulletType(const shared_ptr<Bullet_Type> &bullet)
{
  B_T = bullet;
}

void Spaceship::MoveLeft()
{
  position.x -= speed;
  if (position.x < 0)
  {
    position.x = 0;
  }
}
void Spaceship::MoveRight()
{
  position.x += speed;
  if (position.x > GetScreenWidth() - image.width)
  {
    position.x = GetScreenWidth() - image.width;
  }
}
void Spaceship::FireLaser()
{
  if (GetTime() - timeFire >= 0.2)
  {
    B_T->SHOOT(this->lasers, this->position.x, this->position.y,
               this->image.width, this->timeFire);
  }
}

Rectangle Spaceship::GetRectangle()
{
  float paddingX = 70.0f; // Horizontal padding
  float paddingY = 50.0f; // Vertical padding
  return Rectangle{
      position.x + paddingX,        // X position with padding from left
      position.y + paddingY,        // Y position with padding from top
      image.width - (2 * paddingX), // Width reduced by padding on both sides
      image.height - (2 * paddingY) // Height reduced by padding on top and bottom
  };
}
void Spaceship::TakeDamage(int damage)
{
  health -= damage;
  if (health <= 0)
  {
    health = 0;
  }
}
int Spaceship::GetHealth() const
{
  return health;
}
void Spaceship::changeGun()
{
  int gt = (this->guntype + 1) % 4;
  if (gt == 0)
  {
    setBulletType(make_shared<Normal_B>());
  }
  else if (gt == 1)
  {
    setBulletType(make_shared<Long_B>());
  }
  else if (gt == 2)
  {
    setBulletType(make_shared<Span_B>());
  }
  else if (gt == 3)
  {
    setBulletType(make_shared<watermelon_B>());
  }
  this->guntype = gt;
}

void Spaceship::Reset()
{
  // float margin = 40.0f;
  // float screenWidth = GetScreenWidth() - (2 * margin);
  // float screenHeight = GetScreenHeight() - (2 * margin);

  // // Initialize spaceship position at bottom center of screen
  // float spaceshipX = margin + screenWidth / 2.0f - 32; // 32 is half the spaceship width
  // float spaceshipY = GetScreenHeight() - margin - 60;
  position.x = (GetScreenWidth() - image.width) / 2.0f;
  position.y = GetScreenHeight() - image.height - 100;
  lasers.clear();
}