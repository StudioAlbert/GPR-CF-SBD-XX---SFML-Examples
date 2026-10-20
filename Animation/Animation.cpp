// Animation : seize textures et une horloge, l'animation a la main.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"


constexpr float winFrameRate = 30.F;

int main()
{
	sf::RenderWindow window(sf::VideoMode({800, 600}), "The Game");

	std::vector<sf::Texture> textures;
	std::size_t idxTextures = 0;

	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(static_cast<unsigned int>(winFrameRate));

	// Period = nb Miliseconds / Frame Rate
	constexpr float floatPeriod = (1000.0f / std::min(12.0f, winFrameRate));

	// Animation
	// Load every textures --------------------------------------------------------------------------------------------------
	for (size_t i = 1; i <= 16; i++)
	{
		sf::Texture newTexture;
		std::stringstream path;
		path << "data/sprites/Run" << std::setw(2) << std::setfill('0') << i << ".png";
		std::cout << "Path=" << path.str() << std::endl;

		if (!newTexture.loadFromFile(path.str()))
			return EXIT_FAILURE;

		textures.push_back(newTexture);
	}

	// We need a sprite to display the texture
	sf::Sprite sprite(textures[idxTextures]);
	sprite.setOrigin({textures[idxTextures].getSize().x / 2.0f, textures[idxTextures].getSize().y / 2.0f});
	sprite.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});

	// Time management
	sf::Clock clock;
	sf::Time totalElapsed;

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
		}

		// Graphical Region
		window.clear(sf::Color::Black);


		// Every 100ms, we load a new texture
		sf::Time elapsed = clock.restart();
		totalElapsed = totalElapsed + elapsed;
		std::cout << std::endl << "Counting ..... " << totalElapsed.asMilliseconds() << std::endl;


		if (totalElapsed.asMilliseconds() >= floatPeriod) {
		    // Picking next texture
		    idxTextures++;
		    // Reset time
		    totalElapsed = sf::Time::Zero;
		    // Switch to first frame
		    if (idxTextures >= textures.size())
		    {
			    idxTextures = 7;
		    }
		    std::cout << "New texture index : " << idxTextures << std::endl;
		}

		// Load a texture
		sprite.setTexture(textures[idxTextures]);

		// Display the texture
		window.draw(sprite);

		// Window Display
		window.display();
	}
}
