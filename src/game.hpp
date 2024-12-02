#pragma once
#include "obstacle.hpp"
#include "spaceship.hpp"
#include "aliens.hpp"
#include <unordered_map>
#include "level.hpp"
#include "spaceship.hpp"
#include "aliens.hpp"
#include "bossAlien.hpp"
#include <unordered_map>
#include <memory>
#include "planets.hpp"
#include <iostream>

class Map;
class Game
{
public:
  Game();
  ~Game();
  void Draw();
  void Update();
  void HandleInput();
  bool run;
  int lives;
  int currentLevel;
  int playerCoins = 0;
  void LoadLevel(int level);
  void NextLevel();
  bool gameCompleted;
  Planet currentPlanet;
  bool planetCompleted = false;
  Map *map;
  void StartPlanet(Planet planet);
  void MarkPlanetCompleted(Planet planet);
  bool ShouldReturnToMap() const;
  bool ShouldAccessStore() const;
  void ResetStoreFlag();
  void DrawHealthBar();
  void DeleteInactiveLasers();
  std::vector<Obstacle> createObstacles();
  std::vector<std::shared_ptr<Alien>> createAliens(int rows, int cols);
  std::vector<std::shared_ptr<Alien>> createBoss();
  std::vector<std::shared_ptr<Alien>> createAnimals(int rows, int cols);
  void CheckForCollisions();
  Spaceship spaceship;
  std::vector<Obstacle> obstacles;
  std::vector<std::shared_ptr<Alien>> aliens;

  void MoveAliens();
  void AliensShooter();

  int aliensDirection;
  void MoveAliensDown();
  std::vector<Laser> alienLasers;
  constexpr static float timeAlienShootingInterval = 0.3;
  float timeAlienShooting;

  void GameOver();
  void InitGame();
  void ResetGame();
  std::unordered_map<int, std::shared_ptr<Level>> levelPrototypes;
};