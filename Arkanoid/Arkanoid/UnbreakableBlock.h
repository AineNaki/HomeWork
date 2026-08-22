#pragma once
#include "Block.h"

namespace ArkanoidGame
{
    class UnbreakableBlock : public Block
    {
    protected:
        void OnHit() override { /* пусто Ч блок не разрушаетс€ */ }

    public:
        UnbreakableBlock(const sf::Vector2f& position);
        ~UnbreakableBlock() = default;
    };
}