// Events-c : l'etat du clavier lu directement, hors boucle d'evenements.

#include <iostream>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"


int main()
{
	sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML First Window");

	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	// Setting up the events
	window.setKeyRepeatEnabled(true);

	// Loading a file as texture
	sf::Texture up;
	sf::Texture down;
	sf::Texture left;
	sf::Texture right;
	if (!up.loadFromFile("data/sprites/ZeldaUp.png") ||
		!down.loadFromFile("data/sprites/ZeldaDown.png") ||
		!left.loadFromFile("data/sprites/ZeldaLeft.png") ||
		!right.loadFromFile("data/sprites/ZeldaRight.png"))
		return EXIT_FAILURE;

	// Using a sprite
	// https://www.sfml-dev.org/documentation/3.0.0/classsf_1_1Sprite.html
	// En SFML 3 un sprite ne vit pas sans texture : elle passe par le constructeur.
	sf::Sprite sprite(up);
	sprite.setOrigin({up.getSize().x / 2.0f, up.getSize().y / 2.0f});
	const auto center = window.getSize();
	sprite.setPosition({center.x / 2.0f, center.y / 2.0f});
	//sprite.setScale({0.33f, 0.33f});

	sf::Color background_color(sf::Color::Black);

	const float speed = 8.0f;

	while (window.isOpen())
	{
		sf::Vector2f position;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			// Change texture
			sprite.setTexture(up);
			// Move the sprite
			position = sprite.getPosition();
			position.y -= speed;
			sprite.setPosition(position);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			// Change texture
			sprite.setTexture(down);
			// Move the sprite
			position = sprite.getPosition();
			position.y += speed;
			sprite.setPosition(position);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			// Change texture
			sprite.setTexture(left);
			// Move the sprite
			position = sprite.getPosition();
			position.x -= speed;
			sprite.setPosition(position);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			// Change texture
			sprite.setTexture(right);
			// Move the sprite
			position = sprite.getPosition();
			position.x += speed;
			sprite.setPosition(position);
		}

		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		while (const std::optional event = window.pollEvent())
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(background_color);

		window.draw(sprite);

		// Window Display
		window.display();
	}
}
