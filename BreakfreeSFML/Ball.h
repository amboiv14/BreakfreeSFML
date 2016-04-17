#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "GameObject.h"
#include <iostream>


const float SPEED = 300;

class Ball:public GameObject
{
public:
	Ball(float x, float y, float width, float height);
	~Ball();
	void Update(const sf::Time *deltaTime);
	void Draw();
	void ResetBall(float paddleX, float paddleY);
	void SetDirection(float dirx, float diry);

	struct Direction { float x; float y; } direction;

	sf::Sprite sprite;
	sf::Texture texture;

private:
	void centerPivotPoint();
};

