#include "InputManager.h"



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

sf::Event event;

bool right = false, left = false, space = false;

void InputManager::ExecuteEvents(sf::RenderWindow &window)
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			// window closed
		case sf::Event::Closed:
			window.close();
			break;

			// key pressed
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Left:
				left = true;
				break;
			case sf::Keyboard::Right:
				right = true;
				break;
			case sf::Keyboard::Space:
				space = true;
				break;
			}
			break;
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Left:
				left = false;
				break;
			case sf::Keyboard::Right:
				right = false;
				break;
			case sf::Keyboard::Space:
				space = false;
				break;
			}
		default:
			break;
		}
	}
}
