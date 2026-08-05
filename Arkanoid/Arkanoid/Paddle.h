#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace ArkanoidGame
{
	class Paddle
	{
	public:
			void Init(const sf::Texture& texture);
			void Update(float deltaTime, const sf::RenderWindow& window);
			void Draw(sf::RenderWindow& window) const;
			sf::FloatRect GetBounds() const;
			sf::Vector2f GetPosition() const;

	private:
		sf::Sprite sprite;
		sf::Vector2f position;
		float speed = PADDLE_SPEED;
	
	};
}
