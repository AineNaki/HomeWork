#include "Game.h"
#include <cassert>

namespace ApplesGame
{
    void RestartGame(Game& game)
    {
        game.leaderboard.erase("Player");
        game.background.setFillColor(sf::Color::Black);

        InitPlayer(game.player, game);

        if (game.modeFlags & static_cast<uint32_t>(GameModeFlags::FiniteGoal))
        {
            for (int i = 0; i < game.applesDynamic.size(); ++i)
                game.applesEaten[i] = false;
        }

        for (int i = 0; i < game.applesDynamic.size(); ++i)
        {
            InitApple(game.applesDynamic[i], game.appleTexture);
        }
        for (int i = 0; i < NUM_STONES; ++i)
        {
            InitStone(game.stones[i], game.stoneTexture);
        }
        for (int i = 0; i < NUM_STONES; ++i) {
            while (IsCollide(game.player.position, PLAYER_SIZE, game.stones[i].position, STONE_SIZE)) {
                InitStone(game.stones[i], game.stoneTexture);
            }
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

        game.leaderboard.clear();

        game.leaderboard["ChinaGamer"] = 999; // just joke

        const std::string namesPool[] = { "Alisa", "Noob", "Silver_man", "Love_espresso", "Eve", "Frank", "Grace", "Henry", "Ivy", "Jack" };
        int poolSize = sizeof(namesPool) / sizeof(namesPool[0]);
        int numFake = 5;

        std::vector<std::string> availableNames(namesPool, namesPool + poolSize);
        for (int i = 0; i < numFake; ++i) {
            int idx = rand() % availableNames.size();
            int score = rand() % 201 + 50;
            game.leaderboard[availableNames[idx]] = score;
            availableNames.erase(availableNames.begin() + idx);
        }
        game.stateStack.push(GameStatus::MainMenu);
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

        game.applesDynamic.resize(newCount);
        game.applesEaten.resize(newCount);

        // »нициализируем (позиции €блок и флаги)
        for (int i = 0; i < newCount; ++i)
        {
            game.applesEaten[i] = false;
            InitApple(game.applesDynamic[i], game.appleTexture);
        }
        

        game.numEatenApples = 0;
        UpdateUIScore(game.ui, 0);
        RestartGame(game);
    }

    void CheckAppleCollisions(Game& game)
    {
        bool speedUp = (game.modeFlags & static_cast<uint32_t>(GameModeFlags::SpeedUp)) != 0;
        bool finiteGoal = (game.modeFlags & static_cast<uint32_t>(GameModeFlags::FiniteGoal)) != 0;

        for (int i = 0; i < game.applesDynamic.size(); ++i)
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

    void AddPlayerToLeaderboard(Game& game) {
        auto it = game.leaderboard.find("Player");
        if (it != game.leaderboard.end()) {
            if (game.numEatenApples > it->second) {
                it->second = game.numEatenApples;
            }
        }
        else {
            game.leaderboard["Player"] = game.numEatenApples;
        }
    }

    void CheckStoneCollisions(Game& game)
    {
        for (int i = 0; i < NUM_STONES; ++i)
        {
            if (IsCollide(game.player.position, PLAYER_SIZE,
                game.stones[i].position, STONE_SIZE))
            {
                if (game.GetCurrentState() == GameStatus::Playing)
                {
                    AddPlayerToLeaderboard(game);
                    game.PopState();         
                    game.PushState(GameStatus::GameOver);
                    game.stoneHitSound.play();
                    game.background.setFillColor(sf::Color::Red);
                }
                break; 
            }
        }
    }

    void UpdateGame(Game& game, float deltaTime)
    {
        if (game.GetCurrentState() != GameStatus::Playing)
        {
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
            if (game.GetCurrentState() == GameStatus::Playing)
            {
                AddPlayerToLeaderboard(game);
                game.PopState(); 
                game.PushState(GameStatus::GameOver);
                game.background.setFillColor(sf::Color::Red);
                game.stoneHitSound.play();
            }
        }


        CheckAppleCollisions(game);

        if (game.applesGoal > 0 && game.numEatenApples >= game.applesGoal)
        {
            AddPlayerToLeaderboard(game);
            game.PopState();
            game.PushState(GameStatus::Win);
            game.background.setFillColor(sf::Color::Green);
            return;
        }

        CheckStoneCollisions(game);
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        window.draw(game.background);
        DrawPlayer(game.player, window);

        for (int i = 0; i < game.applesDynamic.size(); ++i)
        {
            if (!game.applesEaten[i])
                DrawApple(game.applesDynamic[i], window);
        }

        for (int i = 0; i < NUM_STONES; ++i)
            DrawStone(game.stones[i], window);

        DrawUI(game.ui, window);

        if (!game.ui.goalText.getString().isEmpty())
            window.draw(game.ui.goalText);
    }

    void DeinitializeGame(Game& game)
    {
      
    }
}