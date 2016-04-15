#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Brick.h"
#include "Paddle.h"

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	bool LoadLevel(int lvl);
	void Draw(sf::RenderWindow &window);
	int getNum();
	void destroyBrick(int index);
	bool loadNextLevel();
	int getLevelData(int lvl, int numOfPositions);

	Brick* Bricks;
	int brickCount = 0;
	int currentLevel = 0;

private:
	const int NUMBER_OF_LEVELS = 3;
	const int COLUMNS = 6;
	const int ROWS = 6;

	

	const int num = 36;
	const int leveldata[3][36] = {
		{ 1, 1, 0, 0, 0, 0,
		0, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 0,
		0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0 },

		{ 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 0,
		0, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 0,
		0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1 },

		{ 0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0 }
	};
};

