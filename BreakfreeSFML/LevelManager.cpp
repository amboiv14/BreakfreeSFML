#include "LevelManager.h"


LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

extern sf::RenderWindow window;

void LevelManager::LoadLevel(int lvl)
{
	float x = 0, y = 0;
	Bricks = new Brick[num];

	for (int i = 0; i < num; i++)
	{
		if (i % COLUMNS == 0 && i != 0)
		{
			y += 32;
			x = 0;
		}

		if (leveldata[lvl][i] != 0)
		Bricks[i] = *new Brick(leveldata[lvl][i]);
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