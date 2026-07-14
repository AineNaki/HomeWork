#include "Apple.h"
#include <deque>

namespace SnakeGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		apple.sprite.setTexture(texture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);

		apple.position.x = (GRID_WIDTH / 2) * CELL_SIZE;
		apple.position.y = (GRID_HEIGHT / 2) * CELL_SIZE;
		apple.sprite.setPosition(apple.position.x, apple.position.y);
	}
	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.sprite.setPosition(apple.position.x, apple.position.y);
		window.draw(apple.sprite);

	}

    void SetAppleTexture(Apple& apple, const sf::Texture& texture)
    {
        apple.sprite.setTexture(texture);
    }

    void UpdateApple(Apple& apple, float deltaTime, const sf::Texture& normalTex, const sf::Texture& goldenTex, const sf::Texture& poisonTex)
    {
        if (apple.isGolden)
        {
            apple.goldenTimer -= deltaTime;
            if (apple.goldenTimer <= 0.f)
            {
                apple.isGolden = false;
                apple.sprite.setTexture(normalTex);
            }
        }
    }


    void RespawnApple(Apple& apple, const std::deque<Position2D>& snakeBody,
        const sf::Texture& normalTex, const sf::Texture& goldenTex, const sf::Texture& poisonTex)
    {
        std::vector<Position2D> occupiedCells;
        for (const auto& segment : snakeBody)
            occupiedCells.push_back(segment);

        bool validPosition = false;
        while (!validPosition)
        {
            int gridX = rand() % GRID_WIDTH;
            int gridY = rand() % GRID_HEIGHT;

            apple.position.x = gridX * CELL_SIZE + CELL_SIZE / 2.f;
            apple.position.y = gridY * CELL_SIZE + CELL_SIZE / 2.f;

            validPosition = true;
            for (const auto& occupied : occupiedCells)
            {
                if (std::abs(apple.position.x - occupied.x) < CELL_SIZE / 2.f &&
                    std::abs(apple.position.y - occupied.y) < CELL_SIZE / 2.f)
                {
                    validPosition = false;
                    break;
                }
            }
        }

        int r = rand() % 100;
        if (r < 15)  // 15% poisoned apple
        {
            apple.isPoison = true;
            apple.isGolden = false;
            apple.sprite.setTexture(poisonTex);
        }
        else if (r < 35)  // 20% golden apple
        {
            apple.isGolden = true;
            apple.isPoison = false;
            apple.goldenTimer = 5.f;
            apple.sprite.setTexture(goldenTex);
        }
        else  // ordinary apple
        {
            apple.isGolden = false;
            apple.isPoison = false;
            apple.sprite.setTexture(normalTex);
        }
    }
        
    
}
