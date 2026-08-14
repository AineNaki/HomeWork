#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Constants.h"

namespace ArkanoidGame
{
	class Brick : public GameObject
	{
	public:
		void Init(const sf::Texture& texture, float x, float y);
		void Draw(sf::RenderWindow& window) const override;
		sf::FloatRect GetBounds() const override;
		bool IsDestroyed() const override { return destroyed; }
		void Destroy() { destroyed = true; }

	private:
		sf::Sprite sprite;
		sf::Vector2f position;
		bool destroyed = false;
	};

}
