#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Brick: public GameObject
{
public:
	Brick();
	Brick(int type, float x, float y, float width, float height);
	Brick(int type);
	~Brick();
	void Update();
	void Draw(sf::RenderWindow &window);

	sf::Texture texture;
	sf::Sprite sprite;
};

