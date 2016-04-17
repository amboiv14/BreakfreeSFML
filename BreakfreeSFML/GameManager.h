#pragma once

#include <SFML/Graphics.hpp>

#include "Paddle.h"
#include "Ball.h"
#include "LevelManager.h"
#include "InputManager.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

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
	void DrawGUI();
	void runGame();
	void CheckPaddleCollisions();
	void CheckBoardCollisions();
	float GetReflection(float hitx) const;
	void GameOver();
	void loseLife();
	void saveScores();
	void loadScores();
	void sortScores();

	const int SCREEN_WIDTH = 768;
	const int SCREEN_HEIGHT = 608;

	const int SCORE_SLOTS = 10;

private:
	int score = 0;
	int lives = 3;

	int gameState = 0;
	int level = 0;

	string name = "<unknown>";

	string playerNames[10];
	int playerScores[10] = { 0 };

	bool gameover;

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

