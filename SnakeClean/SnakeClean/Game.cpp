#include "Game.h"
#include <cassert>
#include <cmath>

namespace SnakeGame
{
    void InitGame(Game& game, sf::RenderWindow& window)
    {
        game.window = &window;

        InitUI(game.ui);

        assert(game.backgroundTexture.loadFromFile(RESOURCES_PATH + "background.png"));
        game.background.setTexture(game.backgroundTexture);

        assert(game.menuBgTexture.loadFromFile(RESOURCES_PATH + "Menu.png"));
        game.menuBg.setTexture(game.menuBgTexture);

        sf::Vector2u menuBgSize = game.menuBgTexture.getSize();
        float menuScaleX = (float)SCREEN_WIDTH / menuBgSize.x;
        float menuScaleY = (float)SCREEN_HEIGHT / menuBgSize.y;
        game.menuBg.setScale(menuScaleX, menuScaleY);
        
        sf::Vector2u textureSize = game.backgroundTexture.getSize();
        float scaleX = (float)SCREEN_WIDTH / textureSize.x;
        float scaleY = (float)SCREEN_HEIGHT / textureSize.y;
        game.background.setScale(scaleX, scaleY);

        assert(game.wallTexture.loadFromFile(RESOURCES_PATH + "stone.png"));
        assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "apple.png"));
        assert(game.goldenAppleTexture.loadFromFile(RESOURCES_PATH + "golden_apple.png"));
        assert(game.poisonAppleTexture.loadFromFile(RESOURCES_PATH + "poison_apple.png"));

        assert(game.snakeHeadRightTex.loadFromFile(RESOURCES_PATH + "head_right.png"));
        assert(game.snakeHeadUpTex.loadFromFile(RESOURCES_PATH + "head_up.png"));
        assert(game.snakeHeadLeftTex.loadFromFile(RESOURCES_PATH + "head_left.png"));
        assert(game.snakeHeadDownTex.loadFromFile(RESOURCES_PATH + "head_down.png"));

        assert(game.snakeBodyHorizontalTex.loadFromFile(RESOURCES_PATH + "body_horizontal.png"));
        assert(game.snakeBodyVerticalTex.loadFromFile(RESOURCES_PATH + "body_vertical.png"));

        assert(game.snakeBodyTopLeftTex.loadFromFile(RESOURCES_PATH + "body_topleft.png"));
        assert(game.snakeBodyTopRightTex.loadFromFile(RESOURCES_PATH + "body_topright.png"));
        assert(game.snakeBodyBottomLeftTex.loadFromFile(RESOURCES_PATH + "body_bottomleft.png"));
        assert(game.snakeBodyBottomRightTex.loadFromFile(RESOURCES_PATH + "body_bottomright.png"));

        assert(game.snakeTailRightTex.loadFromFile(RESOURCES_PATH + "tail_right.png"));
        assert(game.snakeTailUpTex.loadFromFile(RESOURCES_PATH + "tail_up.png"));
        assert(game.snakeTailLeftTex.loadFromFile(RESOURCES_PATH + "tail_left.png"));
        assert(game.snakeTailDownTex.loadFromFile(RESOURCES_PATH + "tail_down.png"));

        assert(game.sound.LoadSounds(RESOURCES_PATH));
        game.sound.PlayMusic();

        game.leaderboard["Player1"] = 100;
        game.leaderboard["Player2"] = 50;
        game.leaderboard["Player3"] = 33;
        game.leaderboard["Player4"] = 23;
        game.leaderboard["Player5"] = 11;
        game.leaderboard["Player6"] = 6;
        game.leaderboard["Player7"] = 5;
        game.leaderboard["Player8"] = 5;
        game.leaderboard["Player9"] = 4;
        game.leaderboard["Player10"] = 2;

        game.stateStack.push(GameStatus::MainMenu);
        RestartGame(game);
    }

    void RestartGame(Game& game)
    {
        game.startDelay = 1.f;
        game.numEatenApples = 0;
        UpdateUIScore(game.ui, 0);
        game.isPoisoned = false;
        game.poisonTimer = 0.f;

        InitSnake(game.snake,
            game.snakeHeadRightTex, game.snakeHeadUpTex, game.snakeHeadLeftTex, game.snakeHeadDownTex,
            game.snakeBodyHorizontalTex, game.snakeBodyVerticalTex,
            game.snakeBodyTopLeftTex, game.snakeBodyTopRightTex,
            game.snakeBodyBottomLeftTex, game.snakeBodyBottomRightTex,
            game.snakeTailRightTex, game.snakeTailUpTex, game.snakeTailLeftTex, game.snakeTailDownTex);

        for (int i = 0; i < 5; ++i)
        {
            InitApple(game.apples[i], game.appleTexture);
            RespawnApple(game.apples[i], game.snake.body, game.appleTexture, game.goldenAppleTexture, game.poisonAppleTexture);
        }

        int wallCount = DIFFICULTY_WALLS[game.difficultyLevel];
        GenerateWalls(game.walls, game.numWalls, wallCount,
            game.snake.body, game.apples[0].position, game.wallTexture);

        game.lastTime = game.gameClock.getElapsedTime().asSeconds();
    }

    void HandleGameOver(Game& game)
    {
        game.ui.finalScoreText.setString("Final Score: " + std::to_string(game.numEatenApples));
        game.ui.finalScoreText.setCharacterSize(24);
        game.ui.finalScoreText.setFillColor(sf::Color::White);
        game.ui.finalScoreText.setPosition(SCREEN_WIDTH - 10.f, 40.f);
        game.ui.finalScoreText.setOrigin(game.ui.finalScoreText.getLocalBounds().width, 0.f);
        game.sound.PlayDeath();
        game.PushState(GameStatus::GameOver);
        bool inTopTen = false;
        if (game.leaderboard.size() < 10)
        {
            inTopTen = true;
        }
        else
        {
            for (const auto& entry : game.leaderboard)
            {
                if (game.numEatenApples > entry.second)
                {
                    inTopTen = true;
                    break;
                }
            }
        }

        if (inTopTen)
        {
            game.waitingForName = true;
            game.playerName = "Player";
        }
        else
        {
            game.leaderboard["Player"] = game.numEatenApples;
        }
    }

    void CheckBorderCollision(Game& game, const Position2D& headPos)
    {
        if (headPos.x < 0.f || headPos.x >= SCREEN_WIDTH ||
            headPos.y < 0.f || headPos.y >= SCREEN_HEIGHT)
        {
            HandleGameOver(game);
        }
    }

    void CheckSelfCollision(Game& game, const Position2D& headPos)
    {
        for (size_t i = 1; i < game.snake.body.size(); ++i)
        {
            if (headPos.x == game.snake.body[i].x &&
                headPos.y == game.snake.body[i].y)
            {
                HandleGameOver(game);
                return;
            }
        }
    }

    void CheckWallCollisions(Game& game, const Position2D& headPos)
    {
        for (int i = 0; i < game.numWalls; ++i)
        {
            bool hit = false;
            for (int l = 0; l < game.walls[i].length; ++l)
            {
                float wx = game.walls[i].position.x + (game.walls[i].isHorizontal ? l * CELL_SIZE : 0);
                float wy = game.walls[i].position.y + (game.walls[i].isHorizontal ? 0 : l * CELL_SIZE);
                if (headPos.x == wx && headPos.y == wy)
                {
                    hit = true;
                    break;
                }
            }
            if (hit)
            {
                HandleGameOver(game);
                return;
            }
        }
    }

    void CheckAppleCollisions(Game& game, const Position2D& headPos)
    {
        for (int i = 0; i < 5; ++i)
        {
            float dx = headPos.x - game.apples[i].position.x;
            float dy = headPos.y - game.apples[i].position.y;
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance < CELL_SIZE / 2.f + APPLE_SIZE / 2.f)
            {
                if (game.apples[i].isPoison)
                {
                    game.isPoisoned = true;
                    game.poisonTimer = POISON_DURATION;
                    game.normalSpeed = game.snake.speed;
                    game.snake.speed = game.normalSpeed + POISON_SPEED_BOOST;
                }

                int scoreToAdd = DIFFICULTY_SCORES[game.difficultyLevel];
                if (game.apples[i].isGolden)
                    scoreToAdd *= 2;

                game.numEatenApples += scoreToAdd;
                game.sound.PlayEat();
                UpdateUIScore(game.ui, game.numEatenApples);

                Position2D newSegment = game.snake.body.back();
                game.snake.body.push_back(newSegment);

                RespawnApple(game.apples[i], game.snake.body, game.appleTexture, game.goldenAppleTexture, game.poisonAppleTexture);
            }
        }
    }

    void UpdateGame(Game& game, float deltaTime)
    {
        GameStatus currentState = game.GetCurrentState();

        if (currentState == GameStatus::Playing)
        {
            UpdateWalls(game.walls, game.numWalls, deltaTime, game.wallMoveTimer,
                game.snake.body, game.apples, game.wallTexture);
        }
        if (game.startDelay > 0.f)
        {
            game.startDelay -= deltaTime;
            return;
        }

        for (int i = 0; i < 5; ++i)
            UpdateApple(game.apples[i], deltaTime, game.appleTexture, game.goldenAppleTexture, game.poisonAppleTexture);
        if (game.isPoisoned)
        {
            game.poisonTimer -= deltaTime;
            if (game.poisonTimer <= 0.f)
            {
                game.isPoisoned = false;
                game.snake.speed = game.normalSpeed;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            if (currentState == GameStatus::Playing)
            {
                game.PushState(GameStatus::Pause);
                sf::sleep(sf::milliseconds(200));
                return;
            }
            else if (currentState == GameStatus::Pause)
            {
                game.PopState();
                sf::sleep(sf::milliseconds(200));
                return;
            }
        }



        if (currentState != GameStatus::Playing)
            return;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            SetSnakeDirection(game.snake, SnakeDirection::Right);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            SetSnakeDirection(game.snake, SnakeDirection::Up);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            SetSnakeDirection(game.snake, SnakeDirection::Left);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            SetSnakeDirection(game.snake, SnakeDirection::Down);

        UpdateSnake(game.snake, deltaTime);

        Position2D headPos = game.snake.body.front();
        CheckBorderCollision(game, headPos);
        CheckSelfCollision(game, headPos);
        CheckWallCollisions(game, headPos);
        CheckAppleCollisions(game, headPos);
    }

    void ApplyDifficulty(Game& game)
    {
        int level = game.difficultyLevel;
        game.snake.speed = DIFFICULTY_SPEEDS[level];
    }

    void DrawGame(Game& game)
    {
        GameStatus currentState = game.GetCurrentState();

        if (currentState == GameStatus::MainMenu)
            return;

        game.window->clear();

        if (currentState == GameStatus::GameOver)
        {
            DrawGameOverScreen(*game.window, game.ui, game.menuBg, game.numEatenApples, game.leaderboard, game.gameOverRestartSelected);
        }
        else
        {
           

            if (game.backgroundTexture.getSize().x > 0)
                game.window->draw(game.background);

            if (game.startDelay > 0.f)
            {
                sf::RectangleShape overlay(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
                overlay.setFillColor(sf::Color(0, 0, 0, 150));
                game.window->draw(overlay);
                DrawGoText(*game.window, game.ui.font);
            }
            else
            {
                for (int i = 0; i < game.numWalls; ++i)
                    DrawWall(game.walls[i], *game.window);

                for (int i = 0; i < 5; ++i)
                    DrawApple(game.apples[i], *game.window);

                DrawSnake(game.snake, *game.window);
            }

            bool isPaused = (currentState == GameStatus::Pause);
            DrawUI(game.ui, *game.window, isPaused);  
        }

        game.window->display();
    }


    void DeinitializeGame(Game& game)
    {
    }
}