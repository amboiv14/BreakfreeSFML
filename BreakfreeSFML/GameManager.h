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
	void runGame();
	void CheckPaddleCollisions() const;
	void CheckBoardCollisions();
	float GetReflection(float hitx) const;

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

private:
	int score = 0;
	int lives = 3;

	int level = 0;

	sf::RenderWindow window;

	sf::Font font;
	sf::Text text;

	sf::Clock timer;
	sf::Time deltaTime;

	Paddle* paddle;

	bool isPlaying = true;
};

