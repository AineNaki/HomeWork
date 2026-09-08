#include "LevelLoader.h"
#include "DurableBlockFactory.h"
#include "SmoothDestroyableBlockFactory.h"
#include "UnbreakableBlockFactory.h"
#include "GlassBlockFactory.h"
#include <fstream>
#include <sstream>

namespace ArkanoidGame
{
    std::vector<std::shared_ptr<Block>> LevelLoader::LoadLevel(const std::string& filePath)
    {
        std::vector<std::shared_ptr<Block>> blocks;

        DurableBlockFactory durableFactory;
        SmoothDestroyableBlockFactory smoothFactory;
        UnbreakableBlockFactory unbreakableFactory;
        GlassBlockFactory glassFactory;

        std::ifstream file(filePath);
        std::string line;
        int row = 0;

        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string type;
            int col = 0;

            while (ss >> type)
            {
                float x = 100.f + col * 110.f;
                float y = 80.f + row * 45.f;
                sf::Vector2f position(x, y);

                if (type == "durable")
                    blocks.push_back(durableFactory.CreateBlock(position));
                else if (type == "smooth")
                    blocks.push_back(smoothFactory.CreateBlock(position));
                else if (type == "unbreakable")
                    blocks.push_back(unbreakableFactory.CreateBlock(position));
                else if (type == "glass")
                    blocks.push_back(glassFactory.CreateBlock(position));

                ++col;
            }
            ++row;
        }

        return blocks;
    }
}