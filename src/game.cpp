#include "game.hpp"
#include "level1_moon.hpp"
#include "level2_moon.hpp"
#include "level3_moon.hpp"
#include "map.hpp"
#include "animals.hpp"
#include "shop.hpp"
Game::Game()
{
  map = new Map(this);
  levelPrototypes[1] = std::make_shared<Level1_moon>();
  levelPrototypes[2] = std::make_shared<Level2_moon>();
  levelPrototypes[3] = std::make_shared<Level3_moon>();
}
Game::~Game()
{
  delete map;
  Alien::UnloadImage();
}
void Game::DrawHealthBar()
{
  float barWidth = 200.0f;
  float barHeight = 20.0f;
  float margin = 40.0f;
  float currentWidth = (spaceship.GetHealth() / (float)spaceship.MAX_HEALTH * barWidth);
  DrawRectangle(margin + 200, margin + 10, barWidth, barHeight, RED);
  DrawRectangle(margin + 200, margin + 10, currentWidth, barHeight, GREEN);
}
void Game::Draw()
{
  spaceship.Draw();
  for (auto &spaceshipLaser : spaceship.lasers)
  {
    spaceshipLaser.Draw();
  }
  for (auto &obstacle : obstacles)
  {
    obstacle.Draw();
  }
  for (auto &alien : aliens)
  {
    alien->Draw();
  }
  for (auto &alienLaser : alienLasers)
  {
    alienLaser.Draw();
  }
}
void Game::Update()
{
  if (run)
  {
    if (aliens.empty())
    {
      NextLevel();
    }
    for (auto &Laser : spaceship.lasers)
    {
      Laser.Update();
    }
    MoveAliens();
    AliensShooter();
    for (auto &laser : alienLasers)
    {
      laser.Update();
    }

    DeleteInactiveLasers();

    // Check all collisions
    CheckForCollisions();
  }
  else
  {
    if (IsKeyDown(KEY_ENTER))
    {

      ResetGame();
      InitGame();
    }
  }
}

void Game::HandleInput()
{
  if (run)
  {
    if (IsKeyDown(KEY_LEFT))
    {
      spaceship.MoveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
      spaceship.MoveRight();
    }
    else if (IsKeyDown(KEY_SPACE))
    {
      spaceship.FireLaser();
    }
  }
}
void Game::DeleteInactiveLasers()
{
  for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
  {
    if (!it->active)
    {
      it = spaceship.lasers.erase(it);
    }
    else
    {
      it++;
    }
  }
  for (auto it = alienLasers.begin(); it != alienLasers.end();)
  {
    if (!it->active)
      it = alienLasers.erase(it);
    else
      ++it;
  }
}
std::vector<Obstacle> Game::createObstacles()
{
  float margin = 40.0f;
  float screenWidth = GetScreenWidth() - (2 * margin);
  float screenHeight = GetScreenHeight() - (2 * margin);

  int obstacleWidth = Obstacle::grid[0].size() * 3;

  float obstacleY = margin + (screenHeight * 0.7f);

  // Calculate gap between obstacles
  float totalObstaclesWidth = obstacleWidth * 4;       // 4 obstacles
  float gap = (screenWidth - totalObstaclesWidth) / 5; // 5 gaps (including edges)

  for (int i = 0; i < 5; i++)
  {
    float offsetX = (i + 1) * gap + i * obstacleWidth;
    obstacles.push_back(Obstacle({offsetX, obstacleY}));
  }
  return obstacles;
}

std::vector<std::shared_ptr<Alien>> Game::createAliens(int rows, int cols)
{
  std::vector<std::shared_ptr<Alien>> aliens;
  float margin = 40.0f;
  float screenWidth = GetScreenWidth() - (2 * margin);

  const float ALIEN_SPACING_X = 50;  // Horizontal space between aliens
  const float ALIEN_SPACING_Y = 40;  // Vertical space between aliens
  const float START_X = margin + 50; // Starting X position
  const float START_Y = margin + 40;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      int alienType;
      if (i == 0)
      {
        alienType = 3;
      }
      if (i == 1)
      {
        alienType = 2;
      }
      if (i > 2)
      {
        alienType = 1;
      }

      float x = START_X + j * ALIEN_SPACING_X;
      float y = START_Y + i * ALIEN_SPACING_Y;
      std::unique_ptr<Effect> effect;
      if (GetRandomValue(0, 1))
      {
        // Assign RainbowEffect
        effect = std::make_unique<Effect>(std::make_shared<RainbowBehavior>());
      }
      else
      {
        // Assign NullEffect (no effect)
        effect = std::make_unique<Effect>(std::make_shared<NullImplementor>());
      }
      aliens.push_back(std::make_shared<Alien>(alienType, Vector2{x, y}, std::move(effect)));
    }
  }
  return aliens;
}
std::vector<std::shared_ptr<Alien>> Game::createAnimals(int rows, int cols)
{
  std::vector<std::shared_ptr<Alien>> animals;
  float margin = 40.0f;
  float screenWidth = GetScreenWidth() - (2 * margin);

  const float ALIEN_SPACING_X = 50;  // Horizontal space between aliens
  const float ALIEN_SPACING_Y = 40;  // Vertical space between aliens
  const float START_X = margin + 50; // Starting X position
  const float START_Y = margin + 40;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      int alienType;
      if (i == 0)
      {
        alienType = 3;
      }
      if (i == 1)
      {
        alienType = 2;
      }
      if (i > 2)
      {
        alienType = 1;
      }

      float x = START_X + j * ALIEN_SPACING_X;
      float y = START_Y + i * ALIEN_SPACING_Y;
      std::unique_ptr<Effect> effect;
      if (GetRandomValue(0, 1))
      {
        // Assign RainbowEffect
        effect = std::make_unique<Effect>(std::make_shared<RainbowBehavior>());
      }
      else
      {
        // Assign NullEffect (no effect)
        effect = std::make_unique<Effect>(std::make_shared<NullImplementor>());
      }
      animals.push_back(std::make_shared<Animal>(alienType, Vector2{x, y}, std::move(effect)));
    }
  }
  return animals;
}
// In game.cpp
std::vector<std::shared_ptr<Alien>> Game::createBoss()
{
  std::vector<std::shared_ptr<Alien>> bossAlien;

  // Calculate center position
  std::unique_ptr<Effect> effect = std::make_unique<Effect>(std::make_shared<NullImplementor>());
  float margin = 40.0f;

  // Initialize spaceship position at bottom center of screen
  float bossX = margin + 100; // 32 is half the spaceship width
  float bossY = margin + 100; // Adjust Y position to be above margin

  // Create single boss alien

  bossAlien.push_back(std::make_shared<BossAlien>(Vector2{bossX, bossY}, std::move(effect)));
  return bossAlien;
}
void Game::MoveAliens()
{
  float margin = 40.0f;
  for (auto &alien : aliens)
  {

    if (alien->position.x + alien->alienImage[alien->type - 1].width > GetScreenWidth() - margin)
    {
      aliensDirection = -abs(aliensDirection);
      MoveAliensDown();
    }
    if (alien->position.x < margin)
    {
      aliensDirection = abs(aliensDirection);
      MoveAliensDown();
    }

    alien->Update(aliensDirection);
  }
}

void Game::CheckForCollisions()
{
  for (auto &laser : spaceship.lasers)
  {
    auto it = aliens.begin();
    while (it != aliens.end())
    {
      if (CheckCollisionRecs((*it)->GetRectangle(), laser.GetRectangle()))
      {
        if ((*it)->GetType() == 4)
        {
          // BossAlien *boss = static_cast<BossAlien *>((&*it->get()));
          BossAlien *boss = static_cast<BossAlien *>((*it).get());
          bool killed = boss->TakeDamage(1);
          laser.active = false;
          if (killed)
          {
            // (*it)->onShotEffect->Init((*it)->position, (*it)->alienImage[(*it)->GetType() - 1]);
            // if ((*it)->onShotEffect->UpdateAndDraw(GetFrameTime())) {
            //   // (*it)->onShotEffect->reset(); // Clear the animation when it's complete
            // }
            ++it;
          }
          else
          {
            ++it;
          }
        }
        else
        {
          // (*it)->onShotEffect->Init((*it)->position, (*it)->alienImage[(*it)->GetType() - 1]);
          // if ((*it)->onShotEffect->UpdateAndDraw(GetFrameTime())) {
          //   // (*it)->onShotEffect->reset(); // Clear the animation when it's complete
          // }
          it = aliens.erase(it);
          laser.active = false;
        }
      }
      else
      {
        ++it;
      }
    }

    for (auto &obstacle : obstacles)
    {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end())
      {
        if (CheckCollisionRecs(it->GetRectangle(), laser.GetRectangle()))
        {
          it = obstacle.blocks.erase(it);
          laser.active = false;
        }
        else
        {
          it++;
        }
      }
    }
  }
  for (auto &laser : alienLasers)
  {
    if (CheckCollisionRecs(spaceship.GetRectangle(), laser.GetRectangle()))
    {
      laser.active = false;
      spaceship.TakeDamage(10);
      if (spaceship.GetHealth() <= 0)
      {
        GameOver();
        return;
      }
    }
    for (auto &obstacle : obstacles)
    {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end())
      {
        if (CheckCollisionRecs(it->GetRectangle(), laser.GetRectangle()))
        {
          it = obstacle.blocks.erase(it);
          laser.active = false;
        }
        else
        {
          it++;
        }
      }
    }
  }

  for (auto &alien : aliens)
  {
    if (alien->GetType() == 4)
    {
      BossAlien *boss = static_cast<BossAlien *>(alien.get());

      for (auto &laser : boss->GetLasers())
      {
        if (CheckCollisionRecs(spaceship.GetRectangle(), laser.GetRectangle()))
        {
          laser.active = false;
          spaceship.TakeDamage(10);
          if (spaceship.GetHealth() <= 0)
          {
            GameOver();
          }
        }
        for (auto &obstacle : obstacles)
        {
          auto it = obstacle.blocks.begin();
          while (it != obstacle.blocks.end())
          {
            if (CheckCollisionRecs(it->GetRectangle(), alien->GetRectangle()))
            {
              it = obstacle.blocks.erase(it);
            }
            else
            {
              it++;
            }
          }
        }
        if (CheckCollisionRecs(spaceship.GetRectangle(), alien->GetRectangle()))
        {
          GameOver();
        }
      }
    }
  }

  aliens.erase(std::remove_if(aliens.begin(), aliens.end(),
                              [](const std::shared_ptr<Alien> &alien) -> bool
                              {
                                if (alien->GetType() == 4) // BossAlien
                                {
                                  BossAlien *boss = static_cast<BossAlien *>(alien.get());
                                  if (boss->isDead && boss->effect->IsComplete())

                                  {
                                    return true; // Remove this alien
                                  }
                                }
                                return false; // Keep this alien
                              }),
               aliens.end());
}

void Game::AliensShooter()
{
  double currentTime = GetTime();
  if (currentTime - timeAlienShooting >= timeAlienShootingInterval && !aliens.empty())
  {
    // Allow 2-3 aliens to shoot at once
    int shootersCount = GetRandomValue(1, 2);
    for (int i = 0; i < shootersCount; i++)
    {
      int randomIndex = GetRandomValue(0, aliens.size() - 1);
      Alien &alien = *aliens[randomIndex];
      alienLasers.push_back(Laser({alien.position.x + alien.alienImage[alien.type - 1].width / 2,
                                   alien.position.y + alien.alienImage[alien.type - 1].height},
                                  6, 0, YELLOW));
    }
    timeAlienShooting = GetTime();
  }
}

void Game::MoveAliensDown()
{
  for (auto &Alien : aliens)
  {
    Alien->position.y += 2;
  }
}

void Game::GameOver()
{
  run = false;
}

void Game::InitGame()
{

  float margin = 40.0f;
  float screenWidth = GetScreenWidth() - (2 * margin);
  float screenHeight = GetScreenHeight() - (2 * margin);

  // Initialize spaceship position at bottom center of screen
  float spaceshipX = margin + screenWidth / 2.0f - 32; // 32 is half the spaceship width
  float spaceshipY = GetScreenHeight() - margin - 200; // Adjust Y position to be above margin
  spaceship.position = {spaceshipX, spaceshipY};
  obstacles = createObstacles();

  // aliensDirection = 2;
  timeAlienShooting = 0;
  spaceship.health = spaceship.MAX_HEALTH;
  run = true;

  currentLevel = 0;
}

void Game::ResetGame()
{
  spaceship.Reset();
  aliens.clear();
  alienLasers.clear();
  obstacles.clear();
}
/*void Game::LoadLevel(int level)
{
  if (level > MAX_LEVEL)
  {
    gameCompleted = true;
    return;
  }
  // Reset necessary elements
  ResetGame();
  obstacles = createObstacles();

  // Reset spaceship position
  float margin = 40.0f;
  float screenWidth = GetScreenWidth() - (2 * margin);
  float spaceshipX = margin + screenWidth / 2.0f - 32;
  float spaceshipY = GetScreenHeight() - margin - 200;
  spaceship.position = {spaceshipX, spaceshipY};
  auto it = levelPrototypes.find(level);
  if (it != levelPrototypes.end())
  {
    std::shared_ptr<Level> levelInstance = it->second->Clone();
    levelInstance->Load(*this);
  }
  else
  {

    std::cerr << "Level prototype not found for level " << level << std::endl;
  }
}*/
// src/game.cpp

void Game::LoadLevel(int levelNumber)
{

  std::unique_ptr<Level> level;
  float margin = 40.0f;
  float screenWidth = GetScreenWidth() - (2 * margin);
  float spaceshipX = margin + screenWidth / 2.0f - 32;
  float spaceshipY = GetScreenHeight() - margin - 200;
  spaceship.position = {spaceshipX, spaceshipY};
  if (currentPlanet == Planet::Earth)
  {
    if (levelNumber == 1)
      level = std::make_unique<Level1_moon>();
    else if (levelNumber == 2)
      level = std::make_unique<Level2_moon>();
    else if (levelNumber == 3)
      level = std::make_unique<Level3_moon>();
  }
  else if (currentPlanet == Planet::Moon)
  {
    if (levelNumber == 1)
      level = std::make_unique<Level1_moon>();
    else if (levelNumber == 2)
      level = std::make_unique<Level2_moon>();
    else if (levelNumber == 3)
      level = std::make_unique<Level3_moon>();
  }
  // Add conditions for other planets

  if (level)
  {
    level->Load(*this);
  }
}
void Game::StartPlanet(Planet planet)
{
  currentPlanet = planet;
  currentLevel = 1;
  planetCompleted = false;
  LoadLevel(currentLevel);
}
bool Game::ShouldReturnToMap() const
{
  return planetCompleted;
}
void Game::MarkPlanetCompleted(Planet planet)
{
  for (auto &planetInfo : map->planets)
  { // Assuming 'map' is accessible
    if (planetInfo.planet == planet)
    {
      planetInfo.completed = true;
      break;
    }
  }
}
void Game::NextLevel()
{
  currentLevel++;
  int maxLevel = 3;
  playerCoins += 100;
  /*Shop shop(*this);
  playerCoins += 100;
  while (shop.IsActive() && currentLevel > 0 && currentLevel < maxLevel)
  {
    shop.Update();
    BeginDrawing();
    shop.Draw();
    EndDrawing();
  }
*/
  if (currentLevel > maxLevel)
  {

    map->MarkPlanetCompleted(currentPlanet);
    planetCompleted = true;
  }
  else
  {
    spaceship.Reset();
    LoadLevel(currentLevel);
  }
}

// Other methods and members
bool Game::ShouldAccessStore() const
{
  return planetCompleted;
}
void Game::ResetStoreFlag()
{
  planetCompleted = false;
}