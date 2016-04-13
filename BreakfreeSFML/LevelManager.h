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

	void LoadLevel(int lvl);
	void Draw(sf::RenderWindow &window);

private:
	const int COLUMNS = 6;
	const int ROWS = 6;

	Brick* Bricks;

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

