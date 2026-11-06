#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

namespace Roguelike
{
    class Block;

    class LevelLoader
    {
    public:
        std::vector<std::shared_ptr<Block>> LoadLevel(const std::string& filePath);
    };
}