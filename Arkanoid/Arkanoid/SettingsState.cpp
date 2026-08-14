#include "SettingsState.h"
#include "Application.h"
#include "GameContext.h"

namespace ArkanoidGame
{
    void SettingsState::HandleInput(GameContext& ctx, Application& app)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            selection = (selection - 1 + 3) % 3;
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            selection = (selection + 1) % 3;
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (selection == 0) { ctx.sound.IncreaseSoundVolume(); ctx.sound.PlayEat(); }
            else if (selection == 1) ctx.sound.IncreaseMusicVolume();
            sf::sleep(sf::milliseconds(100));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (selection == 0) { ctx.sound.DecreaseSoundVolume(); ctx.sound.PlayEat(); }
            else if (selection == 1) ctx.sound.DecreaseMusicVolume();
            sf::sleep(sf::milliseconds(100));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && selection == 2)
        {
            ctx.stateStack.pop();
            sf::sleep(sf::milliseconds(200));
        }
    }

    void SettingsState::Update(GameContext& ctx, float deltaTime)
    {
    }

    void SettingsState::Draw(GameContext& ctx, sf::RenderWindow& window)
    {
        DrawSettingsMenu(ctx.ui, window, selection,
            ctx.sound.GetSoundVolume(), ctx.sound.GetMusicVolume(), ctx.menuBg);
    }
}