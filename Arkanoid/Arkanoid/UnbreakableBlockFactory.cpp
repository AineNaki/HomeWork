#include "UnbreakableBlockFactory.h"
#include "UnbreakableBlock.h"

namespace ArkanoidGame
{
    std::shared_ptr<Block> UnbreakableBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        return std::make_shared<UnbreakableBlock>(position);
    }
}