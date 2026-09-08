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
        int GetScore() const override { return 5; }

        bool ShouldBounceBall() const override;
    };
}