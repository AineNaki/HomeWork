#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "Math.h"
#include "Constants.h"

namespace SnakeGame
{
    struct Apple
    {
        Position2D position;   
        sf::Sprite sprite;   
        bool isGolden = false;
        bool isPoison = false;
        float goldenTimer = 0.f;
    };

    void InitApple(Apple& apple, const sf::Texture& texture);
    void DrawApple(Apple& apple, sf::RenderWindow& window);
    void RespawnApple(Apple& apple, const std::deque<Position2D>& snakeBody,
        const sf::Texture& normalTex, const sf::Texture& goldenTex, const sf::Texture& poisonTex);
    void UpdateApple(Apple& apple, float deltaTime,
        const sf::Texture& normalTex, const sf::Texture& goldenTex, const sf::Texture& poisonTex);

    void SetAppleTexture(Apple& apple, const sf::Texture& texture);
}