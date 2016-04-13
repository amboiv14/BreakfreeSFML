#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void ExecuteEvents(sf::RenderWindow &window);
};

