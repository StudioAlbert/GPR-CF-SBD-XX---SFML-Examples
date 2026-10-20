// Graphics : une forme, son contour, son origine, et la souris pour la deplacer.

#include <iostream>

#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML First Window");

	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	// Define a Shape
	// https://www.sfml-dev.org/documentation/3.0.0/classsf_1_1Shape.html
	sf::RectangleShape shape(sf::Vector2f(50, 50));
	// set the shape color to green
	shape.setFillColor(sf::Color(150, 0, 0));
	// set a 10-pixel wide orange outline
	shape.setOutlineThickness(3.f);
	shape.setOutlineColor(sf::Color(250, 150, 100));
	// define a position
	shape.setOrigin({shape.getSize().x / 2, shape.getSize().y / 2});
	shape.setPosition({0, 0});

	while (window.isOpen())
	{
		//window.clear(sf::Color::Blue);

		const sf::Vector2i pos = sf::Mouse::getPosition(window);
		shape.setPosition(sf::Vector2f(pos));

		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		while (const std::optional event = window.pollEvent())
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		// Draw the shape
		window.draw(shape);

		// Here we draw
		// Draw the sprite
		//window.draw(sprite);

		// effacement les tampons de couleur/profondeur
		window.display();
	}

	return EXIT_SUCCESS;
}
