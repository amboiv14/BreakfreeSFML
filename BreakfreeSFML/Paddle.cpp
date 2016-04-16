#include "Paddle.h"



Paddle::Paddle(float x, float y, float width, float height):GameObject(x, y, width, height)
{
	if (!texture.loadFromFile("Textures/paddle.png"))
		abort();
	sprite.setTexture(texture);
	//sprite.setTextureRect(sf::IntRect(x, y, width, height));
	
	//centerPivotPoint();
	ball = new Ball(x, y - height - 1, height, height);
	ResetPaddle();
	std::cout << "paddles pos: x = " << x << " y = " << y << std::endl;

	if (!buffer.loadFromFile("Sounds/sfxRelease.wav"))
		abort();
	sfxRelease.setBuffer(buffer);
}

Paddle::~Paddle()
{
	delete ball;
}

void Paddle::Update(const sf::Time *deltaTime)
{
	if (!(right && left))
	{
		if (right)
		{
			x += speed * deltaTime->asSeconds();
		}
		else if (left)
		{
			x -= speed * deltaTime->asSeconds();
		}
		sprite.setPosition(x, y);
	}

	if (ballStuck)
	{
		//TODO: Vet ikke hvorfor jeg måtte gange ball.width med 6 for å få ballen
		//til å havne på midten. Burde være å dele på 2. Eller tenker jeg feil?
		ball->x = sprite.getPosition().x - (ball->sprite.getTexture()->getSize().x / 2) + (sprite.getTexture()->getSize().x / 2);
		
		if (space)
		{
			ReleaseBall();
			ball->SetDirection(1, -1);
		}
	}
}

void Paddle::ReleaseBall()
{
	ballStuck = false;
	sfxRelease.play();
}

void Paddle::ResetPaddle()
{
	sprite.setPosition(x, y);
	ball->ResetBall(x, y);
	ballStuck = true;
}

void Paddle::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Paddle::centerPivotPoint()
{
	centerX = x + sprite.getTexture()->getSize().x / 2;
	std::cout << x << std::endl;
	centerY = y + sprite.getTexture()->getSize().y / 2;
}
