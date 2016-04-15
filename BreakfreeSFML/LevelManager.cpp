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
	currentLevel = lvl;
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
		{
			brickCount++;
			Bricks[i] = *new Brick(leveldata[lvl][i], x, y, 128, 32);
			std::cout << "Brick " << i << " xPos = " << Bricks[i].x << " yPos = " << Bricks[i].y << std::endl;
		}
		Bricks[i].sprite.setPosition(Bricks[i].x, Bricks[i].y);
		
		x += 128;
	}
}

void LevelManager::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < num; i++)
	{
		//window.draw(Bricks[i].sprite);
		Bricks[i].Draw(window);
		//std::cout << "Brick " << i << " drawn!" << std::endl;
	}
}

int LevelManager::getNum()
{
	return num;
}

int LevelManager::getLevelData(int lvl, int numOfPositions)
{
	return leveldata[lvl][numOfPositions];
}
