#pragma once
#include "Bonus.h"

namespace ArkanoidGame
{
    class FragileBlocksBonus : public Bonus
    {
    public:
        explicit FragileBlocksBonus(const sf::Vector2f& position);
        void Apply(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks) override;
        void Expire(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks) override;
    };
}