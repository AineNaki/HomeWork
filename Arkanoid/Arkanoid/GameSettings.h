#pragma once

namespace ArkanoidGame
{
    class GameWorld
    {
    public:
        static GameWorld& GetInstance()
        {
            static GameWorld instance;
            return instance;
        }

        // Screen
        float GetScreenWidth() const { return SCREEN_WIDTH; }
        float GetScreenHeight() const { return SCREEN_HEIGHT; }

        // Menu
        float GetMenuTitleY() const { return MENU_TITLE_Y; }
        float GetMenuItemsStartY() const { return MENU_ITEMS_START_Y; }
        float GetMenuItemSpacing() const { return MENU_ITEM_SPACING; }

        // Game
        float GetPaddleSpeed() const { return PADDLE_SPEED; }
        float GetBallSpeed() const { return BALL_SPEED; }
        float GetPaddleWidth() const { return PADDLE_WIDTH; }
        float GetPaddleHeight() const { return PADDLE_HEIGHT; }
        float GetBallSize() const { return BALL_SIZE; }

        // Block
        float GetBlockWidth() const { return BLOCK_WIDTH; }
        float GetBlockHeight() const { return BLOCK_HEIGHT; }
        float GetBreakDelay() const { return BREAK_DELAY; }

    private:
        GameWorld() = default;
        ~GameWorld() = default;
        GameWorld(const GameWorld&) = delete;
        GameWorld& operator=(const GameWorld&) = delete;

        // Screen
        const float SCREEN_WIDTH = 800.f;
        const float SCREEN_HEIGHT = 600.f;

        // Menu
        const float MENU_TITLE_Y = 120.f;
        const float MENU_ITEMS_START_Y = 210.f;
        const float MENU_ITEM_SPACING = 50.f;

        // Game
        const float PADDLE_SPEED = 500.f;
        const float BALL_SPEED = 400.f;
        const float PADDLE_WIDTH = 100.f;
        const float PADDLE_HEIGHT = 20.f;
        const float BALL_SIZE = 15.f;

        // Block
        const float BLOCK_WIDTH = 60.f;
        const float BLOCK_HEIGHT = 20.f;
        const float BREAK_DELAY = 2.f;
    };
}