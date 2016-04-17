#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Ball.h"

extern bool right, left, space;

class Paddle: public GameObject
{
public:
	Paddle(float x, float y, float width, float height);
	~Paddle();

	void Update(const sf::Time *deltaTime);
	void ReleaseBall();
	void ResetPaddle();
	
	Ball* ball;
	bool ballStuck;
	sf::Sprite sprite;
	sf::Texture texture;

	sf::Sound sfxRelease;
private:
	float speed = 250.f;
	float startX = 0, startY = 0;

	void SetSpeed(float newSpeed);
	void centerPivotPoint();

	sf::SoundBuffer buffer;
};

