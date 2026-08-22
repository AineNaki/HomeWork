#pragma once
#include "Block.h"

namespace ArkanoidGame
{
    class GlassBlock : public Block
    {
    protected:
        void OnHit() override;

    public:
        GlassBlock(const sf::Vector2f& position);
        ~GlassBlock() = default;

        bool ShouldBounceBall() const override;
    };
}