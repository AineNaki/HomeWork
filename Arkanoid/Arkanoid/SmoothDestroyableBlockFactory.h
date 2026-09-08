#pragma once
#include "BlockFactory.h"

namespace ArkanoidGame
{
    class SmoothDestroyableBlockFactory final : public BlockFactory
    {
    public:
        ~SmoothDestroyableBlockFactory() override = default;
        std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
    };
}