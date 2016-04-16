#pragma once

#include <SFML/Graphics.hpp>

#include "Paddle.h"
#include "Ball.h"
#include "LevelManager.h"
#include "InputManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	bool init();
	void CheckPaddleOutOfBounds();
	void addScore(int bonus);
	void winLevel();
	void CheckBrickCollisions();
	void runGame();
	void CheckPaddleCollisions() const;
	void CheckBoardCollisions() const;
	float GetReflection(float hitx) const;

	const int SCREEN_WIDTH = 768;
	const int SCREEN_HEIGHT = 608;

private:
	int score = 0;
	int lives = 3;

	int level = 0;

	sf::RenderWindow window;

	sf::Font font;
	sf::Text text;

	sf::Clock timer;
	sf::Time deltaTime;

	LevelManager* levelManager;
	Paddle* paddle;

	bool isPlaying = true;
};

