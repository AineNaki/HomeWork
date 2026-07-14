#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace SnakeGame
{
    struct Apple;

    struct Wall
    {

        Position2D position;
        sf::Sprite sprite;
        int length = 1;  
        bool isHorizontal = true; 

        bool isGhost = false;
        float ghostTimer = 0.f;
        Position2D ghostPosition;
        int ghostLength = 1;
        bool ghostIsHorizontal = true;
    };

    void InitWall(Wall& wall, const sf::Texture& texture);
    void DrawWall(Wall& wall, sf::RenderWindow& window);
    void GenerateWalls(Wall* walls, int& numWalls, int count, const std::deque<Position2D>& snakeBody, const Position2D& applePosition, const sf::Texture& texture);
    void UpdateWalls(Wall* walls, int numWalls, float deltaTime, float& moveTimer, const std::deque<Position2D>& snakeBody, Apple* apples, const sf::Texture& wallTexture);

}
