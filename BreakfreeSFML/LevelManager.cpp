#include "LevelManager.h"


LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

extern sf::RenderWindow window;

bool LevelManager::LoadLevel(int lvl)
{
	currentLevel = lvl;
	if (currentLevel > NUMBER_OF_LEVELS - 1)
	{
		return false;
	}
	
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
			Bricks[i] = *new Brick(leveldata[lvl][i], x, y, 128, 32);
			if (Bricks[i].getType() != 2)
			{
				brickCount++;
			}
			std::cout << "Brick " << i << "type = " << Bricks[i].getType() << " xPos = " << Bricks[i].x << " yPos = " << Bricks[i].y << std::endl;
		}
		Bricks[i].sprite.setPosition(Bricks[i].x, Bricks[i].y);
		
		x += 128;
	}
	return true;
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

bool LevelManager::destroyBrick(int index)
{
	if (Bricks[index].isActive && Bricks[index].getType() != 2)
	{
		Bricks[index].isActive = false;
		brickCount--;
		return true;
	}
	return false;
}

bool LevelManager::loadNextLevel()
{
	bool couldLoadNext = true;
	if (!LoadLevel(currentLevel + 1))
	{
		couldLoadNext = false;
	}
	return couldLoadNext;
}

int LevelManager::getLevelData(int lvl, int numOfPositions)
{
	return leveldata[lvl][numOfPositions];
}
