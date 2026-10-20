// MoveAndJump : forces, vitesse, position, et une collision resolue a la main.

#include <cstdlib>
#include <iostream>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"

const sf::Vector2f kGravityForce = sf::Vector2f(0.0f, 1.0f);

constexpr float kHorizontalMaxSpeed = 10;

int main()
{
	sf::RenderWindow window(sf::VideoMode({800, 600}), "The Game");
	sf::Clock clock;

	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(1000);

	// Define a Shape
	// https://www.sfml-dev.org/documentation/3.0.0/classsf_1_1Shape.html
	sf::RectangleShape player(sf::Vector2f(50, 50));
	// set the shape color to green
	player.setFillColor(sf::Color(150, 0, 0));

	// define a position
	player.setOrigin({player.getSize().x / 2, player.getSize().y / 2});
	player.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});

	sf::Vector2f speed = sf::Vector2f(0, 0);

	sf::Vector2f jump_force;
	sf::Vector2f move_force;

	sf::RectangleShape box(sf::Vector2f(300, 50));
	box.setOrigin({150, 25});
	box.setPosition({400, 500});
	box.setFillColor(sf::Color::Green);

	bool is_collisioning = false;

	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		std::cout << std::endl << "Counting ..... " << elapsed.asMilliseconds() << std::endl;

		bool is_grounded = false;

		if (player.getPosition().y >= (window.getSize().y - player.getSize().y / 2))
			is_grounded = true;

		if (is_collisioning)
			is_grounded = true;

		jump_force = sf::Vector2f(0.0f, 0.0f);
		move_force = sf::Vector2f(0.0f, 0.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			if (is_grounded)
			{
				jump_force = sf::Vector2f(0.0f, -30.0f);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			if (speed.x > (-1 * kHorizontalMaxSpeed))
			{
				move_force = sf::Vector2f(-5.0f, 0.0f);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			if (speed.x < kHorizontalMaxSpeed)
			{
				move_force = sf::Vector2f(5.0f, 0.0f);
			}
		}

		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				speed = sf::Vector2f(0, 0);
				player.setPosition(sf::Vector2f(mousePressed->position));
			}
		}

		// Graphical Region
		window.clear(sf::Color::Black);

		// acceleration is a sum of forces ---------------------------------
		sf::Vector2f acceleration = sf::Vector2f(0, 0);

		if (!is_grounded)
		{
			acceleration += kGravityForce;
		}
		else
		{
			speed.y = 0;
		}

		acceleration += jump_force;
		acceleration += move_force;

		// Speed is a sum of acceleration -----------------------------------------
		speed += acceleration;
		if (!is_grounded)
		{
			speed.x *= 0.75f;
		}
		else
		{
			speed.x *= 0.95f;
		}


		// Position is a sum of speeds -----------------------------------------------

		system("cls");

		player.move(speed);

		if (is_collisioning)
		{
			sf::Vector2f distance = box.getPosition() - player.getPosition();
			distance.x = 0;

			// on recule de la différence entre la distance et la distance max ( = somme des 1/2 tailles)
			float d_max = box.getSize().y / 2.0f + player.getSize().y / 2.0f;
			float d = distance.y;

			std::cout << "D max : " << d_max << " , " << "D : " << d << std::endl;
			distance.y = 1;
			player.move((d - d_max) * distance);
		}
		else
		{
			std::cout << "---------------------------------" << std::endl;
		}

		is_collisioning = player.getGlobalBounds().findIntersection(box.getGlobalBounds()).has_value();

		std::cout << std::endl;
		std::cout << "is grounded ?" << is_grounded << std::endl;
		std::cout << "Acceleration : \tX=" << acceleration.x << ":\tY=" << acceleration.y << std::endl;
		std::cout << "Vitesse : \tX=" << speed.x << ":\tY=" << speed.y << std::endl;
		std::cout << "Position : \tX=" << player.getPosition().x << ":\tY=" << player.getPosition().y << std::endl;

		window.draw(player);
		window.draw(box);

		// Window Display
		window.display();
	}
}
