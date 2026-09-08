#pragma once
#include "BlockFactory.h"

namespace ArkanoidGame
{
    class UnbreakableBlockFactory final : public BlockFactory
    {
    public:
        ~UnbreakableBlockFactory() override = default;
        std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
    };
}