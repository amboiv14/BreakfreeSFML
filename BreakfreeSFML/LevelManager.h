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

	void loadLv0();
	void Draw(sf::RenderWindow &window);

private:
	const int COLUMNS = 6;
	const int ROWS = 6;

	const int num = 36;
	Brick* Bricks;
};

