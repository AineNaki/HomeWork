#include "SmoothDestroyableBlockFactory.h"
#include "SmoothDestroyableBlock.h"

namespace ArkanoidGame
{
    std::shared_ptr<Block> SmoothDestroyableBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        return std::make_shared<SmoothDestroyableBlock>(position);
    }
}