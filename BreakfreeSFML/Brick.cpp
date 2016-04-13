#include "Brick.h"

Brick::Brick()
{
	if (!texture.loadFromFile("Textures/brick0.png"))
		abort();
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 128, 32));
}

Brick::Brick(int type)
{
	if (!texture.loadFromFile("Textures/brick" + std::to_string(type) + ".png"))
		abort();
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 128, 32));
}


Brick::~Brick()
{
}
