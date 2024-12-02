#include "game.hpp"
#include <raylib.h>
#include "map.hpp"
#include "shop.hpp"
typedef enum GameScreen
{
  LOGO = 0,
  TITLE,
  MAP,
  GAMEPLAY,
  STORE,
} GameScreen;

int main()
{
  ;
  Color grey = {29, 29, 27, 255};
  Color yellow = {243, 216, 63, 255};
  // Initialization

  const int screenWidth = 1280;
  const int screenHeight = 900;

  InitWindow(screenWidth, screenHeight, "Space Invaders");

  Image logoImage = LoadImage("Graphics/logo.png");
  ImageResize(&logoImage, logoImage.width / 6, logoImage.height / 6);
  Texture2D logo = LoadTextureFromImage(logoImage);
  UnloadImage(logoImage);
  Texture2D lives = LoadTexture("Graphics/lives.png");
  Texture2D background = LoadTexture("Graphics/background.png");
  // Texture2D lives = LoadTexture("Graphics/live.png");
  if (background.id == 0)
  {
    TraceLog(LOG_ERROR, "Failed to load background texture");
  }
  Font font = LoadFontEx("Fonts/monogram.ttf", 64, 0, 0);
  GameScreen currentScreen = LOGO;
  SetTargetFPS(60);
  int framesCounter = 0;
  Game game;

  // Main game loop
  while (!WindowShouldClose())
  {
    // Update
    switch (currentScreen)
    {
    case LOGO:
    {
      framesCounter++;
      if (framesCounter > 120) // 2 seconds at 60fps
      {
        currentScreen = TITLE;
        framesCounter = 0;
      }
    }
    break;

    case TITLE:
    {
      if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
      {
        currentScreen = MAP;
      }
    }
    break;
    case MAP:
    {
      game.map->Update();
      if (!game.map->IsActive())
      {
        if (game.ShouldAccessStore())
        {
          currentScreen = STORE;
        }
        else
        {
          game.StartPlanet(game.map->GetSelectedPlanet());
          currentScreen = GAMEPLAY;
        }
      }
    }
    break;
    case GAMEPLAY:
    {
      game.HandleInput();
      game.Update();
      if (game.ShouldReturnToMap())
      {
        // If the player finishes the current planet, return to the map
        game.map->Reset(); // Reset the map state if necessary
        currentScreen = MAP;
      }
    }
    break;
    case STORE:
    {
      Shop shop(game);
      while (shop.IsActive())
      {
        shop.Update();
        BeginDrawing();
        ClearBackground(BLACK);
        shop.Draw();
        EndDrawing();
      }
      game.ResetStoreFlag();
      currentScreen = MAP;
      TraceLog(LOG_INFO, "Returning to MAP screen from STORE");

      /* ClearBackground(BLACK);
       DrawText("STORE", screenWidth / 2 - MeasureText("STORE", 40) / 2, 50, 40, WHITE);
       DrawText("Press 1 to buy Health Upgrade", 100, 150, 20, WHITE);
       DrawText("Press 2 to buy Weapon Upgrade", 100, 200, 20, WHITE);
       DrawText("Press ENTER to continue to the next level", 100, 300, 20, WHITE);
       if (IsKeyPressed(KEY_ENTER))
       {

         currentScreen = GAMEPLAY;
       }
       else if (IsKeyPressed(KEY_ONE))
       {
         game.spaceship.TakeDamage(-50);
       }
       else if (IsKeyPressed(KEY_TWO))
       {
         game.spaceship.changeGun();
       }
       */
    }
    break;

    default:
      break;
    }

    // Draw
    BeginDrawing();
    ClearBackground(grey);

    switch (currentScreen)
    {
    case LOGO:
    {
      DrawText("LOADING...", screenWidth / 2 - MeasureText("LOADING...", 40) / 2,
               screenHeight / 2 - 40, 40, WHITE);
      DrawTexture(logo, 0, 0, WHITE);                                                 // Top-left corner
      DrawTexture(logo, screenWidth - logo.width, 0, WHITE);                          // Top-right corner
      DrawTexture(logo, 0, screenHeight - logo.height, WHITE);                        // Bottom-left corner
      DrawTexture(logo, screenWidth - logo.width, screenHeight - logo.height, WHITE); // Bottom-right corner
    }
    break;

    case TITLE:
    {
      if (background.id != 0)
      {
        DrawTexture(background, 0, 0, WHITE);
      }
      DrawText("SPACE INVADERS", screenWidth / 2 - MeasureText("SPACE INVADERS", 60) / 2,
               screenHeight / 3, 60, WHITE);
      DrawText("PRESS ENTER or SPACE to START", screenWidth / 2 - MeasureText("PRESS ENTER or SPACE to START", 20) / 2,
               screenHeight / 2 + 60, 20, WHITE);
    }
    break;
    case MAP:
    {
      if (game.map)
      {
        game.map->Draw();
      }
    }
    break;
    case GAMEPLAY:
    {
      float margin = 40.0f; // Space from screen edges
      float rectWidth = (float)screenWidth - (2 * margin);
      float rectHeight = (float)screenHeight - (2 * margin);

      // Draw rounded rectangle border
      DrawRectangleRoundedLines(
          (Rectangle){
              margin,    // x position
              margin,    // y position
              rectWidth, // width
              rectHeight // height
          },
          0.1f, // roundness (0.0f to 1.0f)
          30,   // segments (higher = smoother)
          3.0f, // thickness
          yellow);
      DrawLineEx({margin, margin + 40}, {margin + rectWidth, margin + 40}, 3, yellow);

      if (game.gameCompleted)
      {
        // Show game completed message
        DrawTextEx(font, "Congratulations! Game Completed!",
                   {margin + 30, margin + 5}, 34, 2, yellow);
        DrawTextEx(font, "Press Enter to play again",
                   {margin + 30, margin + 45}, 34, 2, yellow);
      }
      else if (!game.run)
      {
        // Show game over message
        DrawTextEx(font, "Game Over, press enter to play again",
                   {margin + 30, margin + 5}, 34, 2, yellow);
      }
      else
      {
        // Show current level
        DrawTextEx(font, TextFormat("Level: %d", game.currentLevel),
                   {margin + 30, margin + 5}, 34, 2, yellow);
        // DrawTextEx(font, TextFormat("Lives: %d", game.lives),
        //            {margin + 200, margin + 5}, 34, 2, yellow);
        /*for (int i = 0; i < game.lives; i++)
        {
          DrawTexture(lives, margin + 30 + i * 30, margin + 50, WHITE);
        }*/
        game.DrawHealthBar();
      }

      game.Draw();
    }
    break;
    case STORE:
    {
    }
    default:
      break;
    }
    EndDrawing();
  }
  // De-Initialization
  UnloadTexture(background);
  CloseWindow();

  return 0;
}