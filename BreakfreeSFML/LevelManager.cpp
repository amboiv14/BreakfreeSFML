#include "LevelManager.h"


LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

extern sf::RenderWindow window;

void LevelManager::loadLv0()
{
	float x = 0, y = 0;
	int placed = 0;

	Bricks = new Brick[num];

	for (int i = 0; i < num; i++)
	{
		if (i % COLUMNS == 0 && i != 0)
		{
			y += 32;
			x = 0;
		}
		Bricks[i] = *new Brick(1);

		Bricks[i].sprite.move(x, y);
		x += 128;
	}
}

void LevelManager::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < num; i++)
	{
		window.draw(Bricks[i].sprite);
	}
}