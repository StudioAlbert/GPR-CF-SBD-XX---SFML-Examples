

#include <iostream>
#include <random>

#include "enemy.hpp"
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "motor.h"
#include "starship_player.hpp"

int main()
{
	constexpr sf::Vector2f playerSpawmPosition = {400, 580};

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "The Game");

	Motor motor;
	motor.SetPosition({ 0, 0 });
	motor.SetDirection({ 10,0 });
	motor.SetSpeed(750);

	sf::CircleShape circle;
	circle.setRadius(5);

	sf::Clock clock;
	//sf::Time time = clock.getElapsedTime();

	StarshipPlayer starship_player;
	starship_player.Load(playerSpawmPosition);

	EnemyManager enemies;

	
	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	while (window.isOpen())
	{

		sf::Time deltaTime = clock.restart();


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

				if (keyPressed->scancode == sf::Keyboard::Scancode::E)
				{
					enemies.SpawnEntity({ 400, 0 });
				}

			}

		}

		// Physics FRAME
		sf::Vector2f followMouseDirection = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - circle.getPosition();
		motor.SetDirection(followMouseDirection);

		sf::Vector2f position = motor.Move(deltaTime.asSeconds());
		//std::cout << position.x << ":" << position.y << "\n";
		circle.setPosition(position);

		starship_player.HandleEvent();
		if (starship_player.CheckCollisions(enemies.GetEntities()))
		{
			// Game Play ......................
			starship_player.SetPosition(playerSpawmPosition);

		}
		starship_player.CheckProjectileCollisions(enemies.GetEntities());

		starship_player.Update(window, deltaTime.asSeconds());

		enemies.Update(window, deltaTime.asSeconds());

		//starship_player.setPosition({ 0,0, });

		/*std::vector<StarshipPlayer> players;

		players.emplace_back();*/

		//for (const auto& p : players)
		//{
		//	p.setPosition({0, 0});
		//}

		// Graphical FRAME ---------------------------------------
		window.clear(sf::Color::Black);

		window.draw(circle);
		window.draw(starship_player);

		window.draw(enemies);

		// Window Display
		window.display();


	}



}
