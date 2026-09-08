#pragma once
#include "Block.h"

namespace ArkanoidGame
{
    class DurableBlock : public Block
    {
    protected:
        void OnHit() override;

    public:
        DurableBlock(const sf::Vector2f& position);
        ~DurableBlock() = default;
        int GetScore() const override { return 10; }

    private:
        int hitCount = 3;
        void UpdateColor();
    };
}