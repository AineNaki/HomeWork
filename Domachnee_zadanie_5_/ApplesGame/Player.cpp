#include "Player.h"
#include "Game.h"


namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game)

	{
		player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right;

		// init player sprite
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
		player.baseScale = player.sprite.getScale();
	}

	bool IsPlayerCollidingWithScreenBorder(const Player& player)
	{
		return (player.position.x - PLAYER_SIZE / 2.f < 0.f ||
			player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			player.position.y - PLAYER_SIZE / 2.f < 0.f ||
			player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT);
	}


	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.x, player.position.y);

		
		switch (player.direction)
		{
		case PlayerDirection::Up:
		{
			player.sprite.setScale(player.baseScale.x, player.baseScale.y);
			player.sprite.setRotation(-90.f);
			break;
		}
		case PlayerDirection::Right:
		{
			player.sprite.setScale(player.baseScale.x, player.baseScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::Down:
		{
			player.sprite.setScale(player.baseScale.x, player.baseScale.y);
			player.sprite.setRotation(90.f);
			break;
		}
		case PlayerDirection::Left:
		{
			player.sprite.setScale(-player.baseScale.x, player.baseScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		}

		window.draw(player.sprite);
	}
}
