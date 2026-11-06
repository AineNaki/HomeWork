#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace Roguelike
{
	class Collidable
	{
	public:
		virtual ~Collidable() = default;
		virtual sf::FloatRect GetRect() const = 0;
		virtual bool GetCollision(std::shared_ptr<Collidable> other) const = 0;
	};

}