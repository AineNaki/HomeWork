#include "Paddle.h"
#include "Math.h"

namespace ArkanoidGame
{
	void Paddle::Init(const sf::Texture& texture)
	{
		sprite.setTexture(texture);
		SetSpriteSize(sprite, PADDLE_WIDTH, PADDLE_HEIGHT);
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
		position.x = SCREEN_WIDTH / 2.f;
		position.y = SCREEN_HEIGHT - PADDLE_HEIGHT - 10.f;
		sprite.setPosition(position);

	}

	void Paddle::Update(float deltaTime, const sf::RenderWindow& window)
	{
		// Mouse control (takes priority over keyboard)
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		position.x = (float)mousePos.x;


		bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::D);

		if (leftPressed)
			position.x -= speed * deltaTime;
		if (rightPressed)
			position.x += speed * deltaTime;

		float halfWidth = PADDLE_WIDTH / 2.f;
		if (position.x - halfWidth < 0.f)
			position.x = halfWidth;
		if (position.x + halfWidth > SCREEN_WIDTH)
			position.x = SCREEN_WIDTH - halfWidth;

		sprite.setPosition(position);
	}

	void Paddle::Draw(sf::RenderWindow& window) const
	{
		window.draw(sprite);
	}
	sf::FloatRect Paddle::GetBounds() const
	{
		return sprite.getGlobalBounds();
	}
	sf::Vector2f Paddle::GetPosition() const
	{
		return position;
	}
}
