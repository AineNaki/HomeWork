#pragma once
#include "BlockFactory.h"

namespace ArkanoidGame
{
	class DurableBlockFactory final : public BlockFactory
	{
	public:
		~DurableBlockFactory() override = default;
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
	};
}