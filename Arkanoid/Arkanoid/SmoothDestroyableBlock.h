#pragma once
#include "Block.h"
#include "IDelayedAction.h"

namespace ArkanoidGame
{
    class SmoothDestroyableBlock : public Block, public IDelayedAction
    {
    protected:
        void OnHit() override;

    public:
        SmoothDestroyableBlock(const sf::Vector2f& position);
        ~SmoothDestroyableBlock() = default;

        void Update(float deltaTime) override;

        bool GetCollision(std::shared_ptr<Collidable> collidableObject) const override;

        void FinalAction() override;
        void EachTickAction(float deltaTime) override;
    };
}