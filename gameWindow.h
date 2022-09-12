#pragma once

#include <SFML/Graphics.hpp>

class GameWindow
{
public:
	GameWindow()
	{
		window.create(sf::VideoMode(800, 800), "CHESS");
	};

	sf::RenderWindow* getWindow() { return &window; };

private:

	sf::RenderWindow window;
	
};
