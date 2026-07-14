#pragma once
#include <string>
#include <cstdint>

namespace SnakeGame
{ 
	//Screen
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	//Snake movement net
	const int CELL_SIZE = 20;
	const int GRID_WIDTH = SCREEN_WIDTH / CELL_SIZE;
	const int GRID_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;
	
	//Snake
	const float INITIAL_SPEED = 100.f;
	const int INITIAL_SNAKE_LENGTH = 3;

	//Apples
	const float APPLE_SIZE = 25.f;
	const float POISON_SPEED_BOOST = 50.f;
	const float POISON_DURATION = 7.f;
	//Walls
	const int MAX_WALLS = 20;
	const float WALL_SIZE = 20.f;
	const float WALL_MOVE_INTERVAL = 10.f;

	//GameMode
	const float EASY_SPEED = 80.f;
	const int EASY_WALLS = 0;
	const int EASY_SCORE = 1;

	const float NORMAL_SPEED = 120.f;
	const int NORMAL_WALLS = 3;
	const int NORMAL_SCORE = 2;

	const float HARD_SPEED = 160.f;
	const int HARD_WALLS = 6;
	const int HARD_SCORE = 3;

	const float EXPERT_SPEED = 200.f;
	const int EXPERT_WALLS = 10;
	const int EXPERT_SCORE = 5;

	const float INSANE_SPEED = 250.f;
	const int INSANE_WALLS = 15;
	const int INSANE_SCORE = 10;

	const int DIFFICULTY_COUNT = 5;

	const float DIFFICULTY_SPEEDS[DIFFICULTY_COUNT] = {
		EASY_SPEED, NORMAL_SPEED, HARD_SPEED, EXPERT_SPEED, INSANE_SPEED
	};

	const int DIFFICULTY_WALLS[DIFFICULTY_COUNT] = {
		EASY_WALLS, NORMAL_WALLS, HARD_WALLS, EXPERT_WALLS, INSANE_WALLS
	};

	const int DIFFICULTY_SCORES[DIFFICULTY_COUNT] = {
		EASY_SCORE, NORMAL_SCORE, HARD_SCORE, EXPERT_SCORE, INSANE_SCORE
	};

	//Menu coordinates
	const float MENU_TITLE_Y = 120.f;
	const float MENU_ITEMS_START_Y = 210.f;
	const float MENU_ITEM_SPACING = 50.f;

}