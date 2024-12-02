#include "shop.hpp"
#include "raylib.h"
#include "spaceship.hpp"
#
Shop::Shop(Game &gameInstance) : game(gameInstance), active(true), selectedItemIndex(0)
{
    items.push_back({"Health Boost",
                     "Increase spaceship health by 50.",
                     100,
                     [&]()
                     { game.spaceship.TakeDamage(-50); }});
    items.push_back({"Weapon Upgrade",
                     "Upgrade spaceship weapon.",
                     100,
                     [&]()
                     { game.spaceship.changeGun(); }});
    // Add more items as needed
    items.push_back({"Speed Booster",
                     "Increase spaceship speed.",
                     100,
                     [&]()
                     { game.spaceship.speed += 5; }});
}
void Shop::Update()
{
    if (IsKeyPressed(KEY_DOWN))
    {
        selectedItemIndex = (selectedItemIndex + 1) % items.size();
    }
    if (IsKeyPressed(KEY_UP))
    {
        selectedItemIndex = (selectedItemIndex - 1 + items.size()) % items.size();
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        ShopItem &item = items[selectedItemIndex];
        if (item.purchased)
        {
        }
        else if (game.playerCoins >= item.price)
        {
            game.playerCoins -= item.price;
            item.effect();
            item.purchased = true;
        }
        else
        {
            // Notify insufficient coins
        }
    }
    if (IsKeyPressed(KEY_ESCAPE))
    {
        active = false;
    }
} // src/shop.cpp
void Shop::Draw()
{
    ClearBackground(BLACK);
    DrawText("Shop - Press ESC to exit", 100, 50, 20, WHITE);
    for (size_t i = 0; i < items.size(); ++i)
    {
        Color color = (i == selectedItemIndex) ? YELLOW : WHITE;
        if (items[i].purchased)
        {
            color = GRAY;
        }
        DrawText(items[i].name.c_str(), 100, 100 + i * 30, 20, color);
        DrawText(items[i].description.c_str(), 300, 100 + i * 30, 20, GRAY);
        DrawText(TextFormat("%d", items[i].price), 1000, 100 + i * 30, 20, color);
    }
    DrawText(TextFormat("Coins: %d", game.playerCoins), 100, 400, 20, WHITE);
}
bool Shop::IsActive() const
{
    return active;
}