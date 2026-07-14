#include <deque>
#include "Wall.h"
#include "Apple.h"


namespace SnakeGame
{
    void InitWall(Wall& wall, const sf::Texture& texture)
    {
        wall.sprite.setTexture(texture);
        SetSpriteSize(wall.sprite, CELL_SIZE, CELL_SIZE);
        SetSpriteRelativeOrigin(wall.sprite, 0.5f, 0.5f);
    }
    void GenerateWalls(Wall* walls, int& numWalls, int count,
        const std::deque<Position2D>& snakeBody,
        const Position2D& applePosition,
        const sf::Texture& texture)
    {
        numWalls = count;
        if (count > MAX_WALLS) count = MAX_WALLS;

        for (int i = 0; i < count; ++i)
        {
            InitWall(walls[i], texture);

            walls[i].length = 1 + rand() % 3;
            walls[i].isHorizontal = rand() % 2 == 0;

            bool validPosition = false;
            int attempts = 0;
            const int MAX_ATTEMPTS = 1000;

            while (!validPosition && attempts < MAX_ATTEMPTS)
            {
                attempts++;

                int gridX = rand() % GRID_WIDTH;
                int gridY = rand() % GRID_HEIGHT;

                if (walls[i].isHorizontal && gridX + walls[i].length > GRID_WIDTH) continue;
                if (!walls[i].isHorizontal && gridY + walls[i].length > GRID_HEIGHT) continue;

                walls[i].position.x = gridX * CELL_SIZE;
                walls[i].position.y = gridY * CELL_SIZE;
                validPosition = true;

                for (int l = 0; l < walls[i].length && validPosition; ++l)
                {
                    int checkX = gridX + (walls[i].isHorizontal ? l : 0);
                    int checkY = gridY + (walls[i].isHorizontal ? 0 : l);
                    Position2D checkPos = { checkX * (float)CELL_SIZE, checkY * (float)CELL_SIZE };

                    for (const auto& segment : snakeBody)
                    {
                        if (checkPos.x == segment.x && checkPos.y == segment.y)
                        {
                            validPosition = false;
                            break;
                        }
                    }

                    if (validPosition &&
                        checkPos.x == applePosition.x - CELL_SIZE / 2.f &&
                        checkPos.y == applePosition.y - CELL_SIZE / 2.f)
                    {
                        validPosition = false;
                    }

                    for (int j = 0; j < i && validPosition; ++j)
                    {
                        for (int jl = 0; jl < walls[j].length; ++jl)
                        {
                            float jx = walls[j].position.x + (walls[j].isHorizontal ? jl * CELL_SIZE : 0);
                            float jy = walls[j].position.y + (walls[j].isHorizontal ? 0 : jl * CELL_SIZE);
                            if (checkPos.x == jx && checkPos.y == jy)
                            {
                                validPosition = false;
                                break;
                            }
                        }
                    }
                }
            }

            if (!validPosition)
            {
                walls[i].length = 1;
                walls[i].isHorizontal = true;
                attempts = 0;
                while (!validPosition && attempts < MAX_ATTEMPTS)
                {
                    attempts++;
                    int gridX = rand() % GRID_WIDTH;
                    int gridY = rand() % GRID_HEIGHT;
                    walls[i].position.x = gridX * CELL_SIZE;
                    walls[i].position.y = gridY * CELL_SIZE;
                    validPosition = true;

                    for (const auto& segment : snakeBody)
                    {
                        if (walls[i].position.x == segment.x && walls[i].position.y == segment.y)
                        {
                            validPosition = false; break;
                        }
                    }
                    if (validPosition &&
                        walls[i].position.x == applePosition.x - CELL_SIZE / 2.f &&
                        walls[i].position.y == applePosition.y - CELL_SIZE / 2.f)
                    {
                        validPosition = false;
                    }
                }
            }
        }
    }

    void UpdateWalls(Wall* walls, int numWalls, float deltaTime, float& moveTimer,
        const std::deque<Position2D>& snakeBody,
        Apple* apples, const sf::Texture& wallTexture)
    {
        if (numWalls == 0) return;

        moveTimer += deltaTime;

        // Проверяем призраков
        for (int i = 0; i < numWalls; ++i)
        {
            if (walls[i].isGhost)
            {
                walls[i].ghostTimer -= deltaTime;
                if (walls[i].ghostTimer <= 0.f)
                {
                    walls[i].position = walls[i].ghostPosition;
                    walls[i].length = walls[i].ghostLength;
                    walls[i].isHorizontal = walls[i].ghostIsHorizontal;
                    walls[i].isGhost = false;
                }
            }
        }

       
        if (moveTimer >= WALL_MOVE_INTERVAL)
        {
            moveTimer = 0.f;
            int idx = rand() % numWalls;
            if (!walls[idx].isGhost)
            {
                bool valid = false;
                int attempts = 0;
                while (!valid && attempts < 100)
                {
                    attempts++;
                    int gridX = rand() % GRID_WIDTH;
                    int gridY = rand() % GRID_HEIGHT;
                    int ghostWallLength = 1 + rand() % 3;
                    bool GhostWallHorizontal = rand() % 2 == 0;

                    if (GhostWallHorizontal && gridX + ghostWallLength > GRID_WIDTH) continue;
                    if (!GhostWallHorizontal && gridY + ghostWallLength > GRID_HEIGHT) continue;

                    valid = true;
                    for (int l = 0; l < ghostWallLength && valid; ++l)
                    {
                        float cx = (gridX + (GhostWallHorizontal ? l : 0)) * CELL_SIZE;
                        float cy = (gridY + (GhostWallHorizontal ? 0 : l)) * CELL_SIZE;

                        for (const auto& seg : snakeBody)
                            if (cx == seg.x && cy == seg.y) { valid = false; break; }

                        for (int a = 0; a < 5 && valid; ++a)
                            if (cx == apples[a].position.x - CELL_SIZE / 2 &&
                                cy == apples[a].position.y - CELL_SIZE / 2) {
                                valid = false; break;
                            }

                        for (int w = 0; w < numWalls && valid; ++w)
                        {
                            if (w == idx) continue;
                            for (int wl = 0; wl < walls[w].length; ++wl)
                            {
                                float wx = walls[w].position.x + (walls[w].isHorizontal ? wl * CELL_SIZE : 0);
                                float wy = walls[w].position.y + (walls[w].isHorizontal ? 0 : wl * CELL_SIZE);
                                if (cx == wx && cy == wy) { valid = false; break; }
                            }
                        }
                    }

                    if (valid)
                    {
                        walls[idx].isGhost = true;
                        walls[idx].ghostTimer = 2.f;
                        walls[idx].ghostPosition = { gridX * (float)CELL_SIZE, gridY * (float)CELL_SIZE };
                        walls[idx].ghostLength = ghostWallLength;
                        walls[idx].ghostIsHorizontal = GhostWallHorizontal;
                    }
                }
            }
        }
    }

    void DrawWall(Wall& wall, sf::RenderWindow& window)
    {
        if (wall.isGhost)
        {
            wall.sprite.setColor(sf::Color(255, 255, 255, 100)); 
            wall.sprite.setPosition(wall.ghostPosition.x, wall.ghostPosition.y);
            window.draw(wall.sprite);

            for (int l = 1; l < wall.ghostLength; ++l)
            {
                float x = wall.ghostPosition.x + (wall.ghostIsHorizontal ? l * CELL_SIZE : 0);
                float y = wall.ghostPosition.y + (wall.ghostIsHorizontal ? 0 : l * CELL_SIZE);
                wall.sprite.setPosition(x, y);
                window.draw(wall.sprite);
            }
        }

        wall.sprite.setColor(sf::Color::White); 
        wall.sprite.setPosition(wall.position.x, wall.position.y);
        window.draw(wall.sprite);

        for (int l = 1; l < wall.length; ++l)
        {
            float x = wall.position.x + (wall.isHorizontal ? l * CELL_SIZE : 0);
            float y = wall.position.y + (wall.isHorizontal ? 0 : l * CELL_SIZE);
            wall.sprite.setPosition(x, y);
            window.draw(wall.sprite);
        }
    }
}