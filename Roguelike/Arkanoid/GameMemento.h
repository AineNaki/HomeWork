#pragma once
#include <SFML/Graphics.hpp>

namespace Roguelike
{
    class GameMemento
    {
    public:
        GameMemento(int lives, const sf::Vector2f& ballPosition)
            : lives(lives), ballPosition(ballPosition) {
        }

        int GetLives() const { return lives; }
        sf::Vector2f GetBallPosition() const { return ballPosition; }

    private:
        int lives;
        sf::Vector2f ballPosition;
    };
}