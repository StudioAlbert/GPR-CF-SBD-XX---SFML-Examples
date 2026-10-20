// Events-d : la manette, ses axes et sa zone morte.

#include <cmath>
#include <iostream>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"


constexpr unsigned int kJoystickId = 0;
constexpr float kJoystickDeadZone = 6.f;
constexpr int kTilemapSize = 24;
constexpr int kTilemapOffset = 1;

int main()
{
	sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML First Window");

	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	// Setting up the events
	window.setKeyRepeatEnabled(true);
	const auto winCenter = window.getSize();

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

	// Une seule tuile decoupee dans la planche : le rectangle est un coin + une taille.
	sf::Texture tilemap;
	if (!tilemap.loadFromFile("data/sprites/KenneyPlatformer_Character.png", false,
		sf::IntRect({6 * (kTilemapSize + kTilemapOffset), 1 * (kTilemapSize + kTilemapOffset)},
			{kTilemapSize, kTilemapSize})))
		return EXIT_FAILURE;

	// Using a sprite
	// https://www.sfml-dev.org/documentation/3.0.0/classsf_1_1Sprite.html
	sf::Sprite tilemapSprite(tilemap);
	tilemapSprite.setOrigin({tilemap.getSize().x / 2.0f, tilemap.getSize().y / 2.0f});
	tilemapSprite.setPosition({winCenter.x / 2.0f, winCenter.y / 2.0f});

	sf::Sprite sprite(up);
	sprite.setOrigin({up.getSize().x / 2.0f, up.getSize().y / 2.0f});
	sprite.setPosition({winCenter.x / 2.0f, winCenter.y / 2.0f});
	sprite.setScale({1.5f, 1.5f});

	sf::Color backgroundColor(sf::Color::Black);

	float axisYPosition = 0.f;
	float axisXPosition = 0.f;

	while (window.isOpen())
	{
		constexpr float speed = 8.0f;

		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		while (const std::optional event = window.pollEvent())
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* joystickMoved = event->getIf<sf::Event::JoystickMoved>())
			{
				std::cout << "Joystick moved " << joystickMoved->joystickId
					<< " : " << static_cast<int>(joystickMoved->axis)
					<< " : " << joystickMoved->position << std::endl;

				if (joystickMoved->joystickId == kJoystickId)
				{
					switch (joystickMoved->axis)
					{
					case sf::Joystick::Axis::Y:
						axisYPosition = joystickMoved->position;
						if (std::abs(axisYPosition) <= kJoystickDeadZone)
							axisYPosition = 0.f;
						break;

					case sf::Joystick::Axis::X:
						axisXPosition = joystickMoved->position;
						if (std::abs(axisXPosition) <= kJoystickDeadZone)
							axisXPosition = 0.f;
						break;

					case sf::Joystick::Axis::Z:
					case sf::Joystick::Axis::R:
					case sf::Joystick::Axis::U:
					case sf::Joystick::Axis::V:
					case sf::Joystick::Axis::PovX:
					case sf::Joystick::Axis::PovY:
						break;
					}
				}
			}
		}

		// Move the sprite
		sf::Vector2f position = sprite.getPosition();

		// Change texture
		if (std::abs(axisYPosition) > std::abs(axisXPosition))
		{
			if (axisYPosition < 0) {
				sprite.setTexture(up);
			}
			else if (axisYPosition > 0) {
				sprite.setTexture(down);
			}
			position.y += (axisYPosition / 100.f) * speed;
		}
		else {
			if (axisXPosition < 0) {
				sprite.setTexture(left);
			}
			else if (axisXPosition > 0) {
				sprite.setTexture(right);
			}
			position.x += (axisXPosition / 100.f) * speed;
		}
		sprite.setPosition(position);

		// Window Display
		window.clear(backgroundColor);
		//window.draw(sprite);
		window.draw(tilemapSprite);
		window.display();
	}
}
