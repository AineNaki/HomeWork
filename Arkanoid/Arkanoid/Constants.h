#pragma once
#include <string>
#include <cstdint>

namespace ArkanoidGame
{
	// Screen
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	// Menu coordinates
	const float MENU_TITLE_Y = 120.f;
	const float MENU_ITEMS_START_Y = 210.f;
	const float MENU_ITEM_SPACING = 50.f;

	// Game
	const float PADDLE_SPEED = 500.f;
	const float BALL_SPEED = 400.f;
	const float PADDLE_WIDTH = 100.f;
	const float PADDLE_HEIGHT = 20.f;
	const float BALL_SIZE = 15.f;

	//Block
	const float BLOCK_WIDTH = 60.f;
	const float BLOCK_HEIGHT = 20.f;
	const float BREAK_DELAY = 2.f;
}