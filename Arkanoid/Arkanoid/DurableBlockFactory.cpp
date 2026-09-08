#include "DurableBlockFactory.h"
#include "DurableBlock.h"

namespace ArkanoidGame
{
    std::shared_ptr<Block> DurableBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        return std::make_shared<DurableBlock>(position);
    }
}