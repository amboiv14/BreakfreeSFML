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
	if (!texture.loadFromFile("Textures/brick" + std::to_string(type) + ".png"))
		abort();
	sprite.setTexture(texture);
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
	window.draw(sprite);
}
