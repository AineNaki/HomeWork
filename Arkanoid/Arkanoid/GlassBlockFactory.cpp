#include "GlassBlockFactory.h"
#include "GlassBlock.h"

namespace ArkanoidGame
{
    std::shared_ptr<Block> GlassBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        return std::make_shared<GlassBlock>(position);
    }
}