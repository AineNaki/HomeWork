#include "Game.h"
#include <cassert>

namespace ApplesGame
{
    void RestartGame(Game& game)
    {
        game.status = GameStatus::Playing;
        game.background.setFillColor(sf::Color::Black);

        InitPlayer(game.player, game);

        if (game.applesEaten && (game.modeFlags & static_cast<uint32_t>(GameModeFlags::FiniteGoal)))
        {
            for (int i = 0; i < game.applesCount; ++i)
                game.applesEaten[i] = false;
        }

        for (int i = 0; i < game.applesCount; ++i)
        {
            InitApple(game.applesDynamic[i], game.appleTexture);
        }
        for (int i = 0; i < NUM_STONES; ++i)
        {
            InitStone(game.stones[i], game.stoneTexture);
        }

        game.numEatenApples = 0;
        UpdateUIScore(game.ui, 0);
        game.lastTime = game.gameClock.getElapsedTime().asSeconds();
    }

    void InitGame(Game& game)
    {
        assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
        assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
        assert(game.stoneTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));

        assert(game.eatSoundBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
        game.eatSound.setBuffer(game.eatSoundBuffer);

        assert(game.stoneHitSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
        game.stoneHitSound.setBuffer(game.stoneHitSoundBuffer);

        assert(game.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
        InitUI(game.ui, game.font);

        game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        game.background.setFillColor(sf::Color::Black);
        game.background.setPosition(0.f, 0.f);

        game.applesDynamic = nullptr;
        game.applesEaten = nullptr;
        game.applesCount = 0;
    }

    void ApplyGameMode(Game& game)
    {
        bool speedUpEnabled = (game.modeFlags & static_cast<uint32_t>(GameModeFlags::SpeedUp)) != 0;
        bool fiftyApples = (game.modeFlags & static_cast<uint32_t>(GameModeFlags::FiftyApples)) != 0;
        bool finiteGoal = (game.modeFlags & static_cast<uint32_t>(GameModeFlags::FiniteGoal)) != 0;

        int newCount;
        if (finiteGoal)
        {
            game.applesGoal = 20 + rand() % 31;
            newCount = game.applesGoal;
            game.ui.goalText.setString("Goal: " + std::to_string(game.applesGoal));
        }
        else {
            game.applesGoal = 0;
            newCount = fiftyApples ? 50 : 20;
            game.ui.goalText.setString("");
        }

        if (newCount != game.applesCount)
        {
            delete[] game.applesDynamic;
            delete[] game.applesEaten;

            game.applesCount = newCount;
            game.applesDynamic = new Apple[newCount];
            game.applesEaten = new bool[newCount];

            for (int i = 0; i < newCount; ++i)
            {
                game.applesEaten[i] = false;
                InitApple(game.applesDynamic[i], game.appleTexture);
            }
        }
        else {
            for (int i = 0; i < game.applesCount; ++i)
            {
                game.applesEaten[i] = false;
                InitApple(game.applesDynamic[i], game.appleTexture);
            }
        }

        game.numEatenApples = 0;
        UpdateUIScore(game.ui, 0);
        RestartGame(game);
    }

    void CheckAppleCollisions(Game& game)
    {
        bool speedUp = (game.modeFlags & static_cast<uint32_t>(GameModeFlags::SpeedUp)) != 0;
        bool finiteGoal = (game.modeFlags & static_cast<uint32_t>(GameModeFlags::FiniteGoal)) != 0;

        for (int i = 0; i < game.applesCount; ++i)
        {
            if (!IsCollide(game.player.position, PLAYER_SIZE,
                game.applesDynamic[i].position, APPLE_SIZE))
                continue;

            if (finiteGoal) {
                if (!game.applesEaten[i]) {
                    game.applesEaten[i] = true;
                    ++game.numEatenApples;
                    UpdateUIScore(game.ui, game.numEatenApples);
                    game.eatSound.play();
                }
            }
            else {
                ++game.numEatenApples;
                UpdateUIScore(game.ui, game.numEatenApples);
                if (speedUp) game.player.speed += ACCELERATION;
                game.eatSound.play();
                InitApple(game.applesDynamic[i], game.appleTexture);
            }
        }
    }

    void CheckStoneCollisions(Game& game)
    {
        for (int i = 0; i < NUM_STONES; ++i)
        {
            if (IsCollide(game.player.position, PLAYER_SIZE,
                game.stones[i].position, STONE_SIZE))
            {
                game.status = GameStatus::GameOver;
                game.stoneHitSound.play();
                game.background.setFillColor(sf::Color::Red);
                break;
            }
        }
    }

    void UpdateGame(Game& game, float deltaTime)
    {
        if (game.status != GameStatus::Playing)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                RestartGame(game);
                sf::sleep(sf::seconds(1));
                game.lastTime = game.gameClock.getElapsedTime().asSeconds();
            }
            return;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            game.player.direction = PlayerDirection::Right;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            game.player.direction = PlayerDirection::Up;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            game.player.direction = PlayerDirection::Left;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            game.player.direction = PlayerDirection::Down;

        switch (game.player.direction)
        {
        case PlayerDirection::Right:
            game.player.position.x += game.player.speed * deltaTime;
            break;
        case PlayerDirection::Up:
            game.player.position.y -= game.player.speed * deltaTime;
            break;
        case PlayerDirection::Left:
            game.player.position.x -= game.player.speed * deltaTime;
            break;
        case PlayerDirection::Down:
            game.player.position.y += game.player.speed * deltaTime;
            break;
        }

        if (IsPlayerCollidingWithScreenBorder(game.player))
        {
            game.status = GameStatus::GameOver;
            game.background.setFillColor(sf::Color::Red);
            game.stoneHitSound.play();
        }

        CheckAppleCollisions(game);

        if (game.applesGoal > 0 && game.numEatenApples >= game.applesGoal)
        {
            game.status = GameStatus::Win;
            game.background.setFillColor(sf::Color::Green);
            return;
        }

        CheckStoneCollisions(game);
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        window.draw(game.background);
        DrawPlayer(game.player, window);

        for (int i = 0; i < game.applesCount; ++i)
        {
            if (!game.applesEaten[i])
                DrawApple(game.applesDynamic[i], window);
        }

        for (int i = 0; i < NUM_STONES; ++i)
            DrawStone(game.stones[i], window);

        DrawUI(game.ui, window);

        if (game.status == GameStatus::GameOver)
            window.draw(game.ui.gameOverText);
        else if (game.status == GameStatus::Win)
            window.draw(game.ui.winText);

        if (!game.ui.goalText.getString().isEmpty())
            window.draw(game.ui.goalText);
    }

    void DeinitializeGame(Game& game)
    {
        delete[] game.applesDynamic;
        delete[] game.applesEaten;
        game.applesDynamic = nullptr;
        game.applesEaten = nullptr;
        game.applesCount = 0;
    }
}