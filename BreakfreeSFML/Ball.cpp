#include "Ball.h"

Ball::Ball(float x, float y, float width, float height):GameObject(x, y, width, height)
{
	if (!texture.loadFromFile("Textures/ball.png"))
		abort();
	sprite.setTexture(texture);
	//ball.setTextureRect(sf::IntRect(0, 0, 16, 16));
	//centerPivotPoint();
	ResetBall(x, y);

	//TODO: sprite.setOrigin(8, 8);
}


Ball::~Ball()
{
}

void Ball::Update(const sf::Time *deltaTime)
{
	//std::cout << deltaTime->asSeconds();
	x += direction.x * SPEED * deltaTime->asSeconds();
	y += direction.y * SPEED * deltaTime->asSeconds();
	sprite.setPosition(x, y);
}


//TODO: Fjerne denne hvis den ikke trengs
void Ball::Draw()
{
	//sprite.move(x, y);
}


void Ball::SetDirection(float x, float y)
{
	direction.x = x;
	direction.y = y;

	/*float length = sqrt(x * x + y * y);
	this->direction.x = SPEED * (x / length);
	this->direction.y = SPEED * (y / length);*/
}

void Ball::centerPivotPoint()
{
	x += sprite.getTexture()->getSize().x / 2;
	std::cout << x << std::endl;
	y += sprite.getTexture()->getSize().y / 2;
}

void Ball::ResetBall(float paddleX, float paddleY)
{
	x = paddleX;
	y = paddleY - height;
	direction.x = 0;
	direction.y = 0;
	//sprite.setPosition(392, 536);
	std::cout << "Ball pos: x = " << x << " y = " << y << std::endl;
}

