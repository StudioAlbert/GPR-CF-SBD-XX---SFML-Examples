// OOPHero : le heros devient une classe, sf::Drawable et sf::Transformable.

#include <iostream>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"

#include "player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "SFML First Window");

	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	// Setting up the events
	window.setKeyRepeatEnabled(true);

	Player player;

	sf::Color background_color(sf::Color::Black);

	while (window.isOpen())
	{
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					window.close();
			}

			//player.HandleEvent(event);
		}

		player.Update();

		window.clear(background_color);

		window.draw(player);

		// Window Display
		window.display();
	}
}
