#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <string>

class Brick: public GameObject
{
public:
	Brick();
	Brick(int type, float x, float y, float width, float height);
	Brick(int type);
	~Brick();
	void Update();
	void Draw(sf::RenderWindow &window);
	int getType();
	int getScore();

	bool isActive = false;

	sf::Texture texture;
	sf::Sprite sprite;
private:
	//0 = none, 1 = normal, 2 = unbreakable
	int type = 0;
	int score = 0;
};

