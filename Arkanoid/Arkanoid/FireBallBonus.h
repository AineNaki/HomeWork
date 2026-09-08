#pragma once
#include "Bonus.h"

namespace ArkanoidGame
{
    class FireBallBonus : public Bonus
    {
    public:
        explicit FireBallBonus(const sf::Vector2f& position);
        void Apply(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks) override;
        void Expire(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks) override;
    };
}