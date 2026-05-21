#pragma once
#include <string>

namespace ApplesGame
{

	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const float INITIAL_SPEED = 100.f;
	const float PLAYER_SIZE = 20.f;
	const float ACCELERATION = 20.f;
	const float APPLE_SIZE = 20.f;
	const int NUM_STONES = 3;
	const float STONE_SIZE = 20.f;
    
	enum class GameModeFlags : uint32_t
	{
		None = 0,
		SpeedUp = 1 << 0,
		FiftyApples = 1 << 1,
		FiniteGoal = 1 << 2
	};
}