#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Brick: public GameObject
{
public:
	Brick();
	Brick(int type);
	~Brick();

	sf::Texture texture;
	sf::Sprite sprite;
};

