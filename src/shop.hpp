// src/shop.hpp
#include <vector>
#include <string>
#include <functional>
#include "game.hpp"
struct ShopItem
{
    std::string name;
    std::string description;
    int price;
    std::function<void()> effect;
    bool purchased = false;
};

class Shop
{
public:
    Shop(Game &gameInstance);
    void Update();
    void Draw();
    bool IsActive() const;

private:
    Game &game;
    bool active = true;
    int selectedItemIndex = 0;
    std::vector<ShopItem> items;
};