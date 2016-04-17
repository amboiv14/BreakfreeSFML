#include "Brick.h"


Brick::Brick()
{
	/*if (!texture.loadFromFile("Textures/brick0.png"))
		abort();
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 128, 32));*/
}

Brick::Brick(int type, float x, float y, float width, float height):GameObject(x, y, width, height)
{
	this->type = type;
	if (!texture.loadFromFile("Textures/brick" + std::to_string(type) + ".png"))
		abort();
	sprite.setTexture(texture);
	score = 100 * type;
	isActive = true;
	//sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

Brick::Brick(int type)
{

}


Brick::~Brick()
{
}

void Brick::Update()
{

}

void Brick::Draw(sf::RenderWindow &window)
{
	if (isActive)
	{
		window.draw(sprite);
	}
}

int Brick::getType()
{
	return type;
}

int Brick::getScore()
{
	return score;
}
