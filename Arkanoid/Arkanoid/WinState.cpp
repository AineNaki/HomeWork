#include "WinState.h"
#include "Application.h"
#include "GameContext.h"

namespace ArkanoidGame
{
    void WinState::HandleInput(GameContext& ctx, Application& app)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            restartSelected = !restartSelected;
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            restartSelected = !restartSelected;
            sf::sleep(sf::milliseconds(150));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            if (restartSelected)
                app.ResetToPlaying();
            else
                app.ResetToMainMenu();
            sf::sleep(sf::milliseconds(200));
        }
    }

    void WinState::Update(GameContext& ctx, float deltaTime)
    {
    }

    void WinState::Draw(GameContext& ctx, sf::RenderWindow& window)
    {
        window.clear();

        sf::Text title;
        title.setFont(ctx.ui.font);
        title.setString("YOU WIN!");
        title.setCharacterSize(48);
        title.setFillColor(sf::Color::Green);
        sf::FloatRect tb = title.getLocalBounds();
        title.setOrigin(tb.width / 2.f, tb.height / 2.f);
        title.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 80);
        window.draw(title);

        sf::Text restartBtn;
        restartBtn.setFont(ctx.ui.font);
        restartBtn.setString("Restart");
        restartBtn.setCharacterSize(28);
        restartBtn.setFillColor(restartSelected ? sf::Color::Green : sf::Color::White);
        sf::FloatRect rb = restartBtn.getLocalBounds();
        restartBtn.setOrigin(rb.width / 2.f, rb.height / 2.f);
        restartBtn.setPosition(SCREEN_WIDTH / 2.f - 70, SCREEN_HEIGHT - 60);
        window.draw(restartBtn);

        sf::Text menuBtn;
        menuBtn.setFont(ctx.ui.font);
        menuBtn.setString("Menu");
        menuBtn.setCharacterSize(28);
        menuBtn.setFillColor(!restartSelected ? sf::Color::Green : sf::Color::White);
        sf::FloatRect mb = menuBtn.getLocalBounds();
        menuBtn.setOrigin(mb.width / 2.f, mb.height / 2.f);
        menuBtn.setPosition(SCREEN_WIDTH / 2.f + 70, SCREEN_HEIGHT - 60);
        window.draw(menuBtn);
    }
}