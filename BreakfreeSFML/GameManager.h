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
	void CheckPaddleCollisions();
	void CheckBoardCollisions();
	float GetReflection(float hitx) const;

	const int SCREEN_WIDTH = 768;
	const int SCREEN_HEIGHT = 608;

private:
	int score = 0;
	int lives = 3;

	int gameState = 0;
	int level = 0;

	sf::RenderWindow window;

	sf::Font font;
	sf::Text text;

	sf::Clock timer;
	sf::Time deltaTime;
	//sf::Time now;
	//sf::Time nextUpdates;

	LevelManager* levelManager;
	Paddle* paddle;

	bool isPlaying = true;

	sf::SoundBuffer buf_hit0, buf_hit1, buf_hit2, buf_paddle;
	sf::Sound sfxHit0, sfxHit1, sfxHit2, sfxPaddle;
};

