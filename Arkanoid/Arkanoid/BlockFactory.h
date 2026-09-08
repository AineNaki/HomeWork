#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	class Block;

	class BlockFactory
	{
	public:
		virtual ~BlockFactory() = default;
		virtual std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) = 0;
	};
}