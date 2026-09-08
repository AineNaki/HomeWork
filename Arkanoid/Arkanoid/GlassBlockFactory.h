#pragma once
#include "BlockFactory.h"

namespace ArkanoidGame
{
    class GlassBlockFactory final : public BlockFactory
    {
    public:
        ~GlassBlockFactory() override = default;
        std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
    };
}