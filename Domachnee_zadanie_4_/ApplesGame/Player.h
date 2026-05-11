#pragma once
#include<SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"
namespace ApplesGame
{
    enum class PlayerDirection
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct Player
    {
        Position2D position;
        float speed = INITIAL_SPEED;
        PlayerDirection direction = PlayerDirection::Right;
        sf::Sprite sprite;
        sf::Vector2f baseScale;
    };

    struct Game;

    void InitPlayer(Player& player, const Game& game);
    bool IsPlayerCollidingWithScreenBorder(const Player& player);
    void DrawPlayer(Player& player, sf::RenderWindow& window);
}