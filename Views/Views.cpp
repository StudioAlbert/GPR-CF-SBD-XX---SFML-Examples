// Views : la camera. On deplace et on zoome la vue, pas le monde.

#include <iostream>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode({800, 600}), "Views",
		sf::Style::Default, sf::State::Windowed,
		sf::ContextSettings{.antiAliasingLevel = 8});

	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	sf::Texture bgFile;
	if (!bgFile.loadFromFile("data/village.png"))
		return EXIT_FAILURE;
	bgFile.setSmooth(true);

	sf::Sprite background(bgFile);
	background.setOrigin({bgFile.getSize().x / 2.0f, bgFile.getSize().y / 2.0f});
	background.setPosition({0, 0});

	sf::View view({0, 0}, sf::Vector2f(window.getSize()));
	window.setView(view);

	sf::CircleShape center_mark;
	center_mark.setRadius(5);
	center_mark.setOrigin({5, 5});
	center_mark.setPosition({0, 0});
	center_mark.setFillColor(sf::Color::Red);
	center_mark.setOutlineThickness(1.0F);
	center_mark.setOutlineColor(sf::Color::Red);

	while (window.isOpen())
	{
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		while (const std::optional event = window.pollEvent())
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* resized = event->getIf<sf::Event::Resized>())
			{
				view.setSize(sf::Vector2f(resized->size));
				window.setView(view);
			}
			else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
			{
				if (keyReleased->code == sf::Keyboard::Key::Left)
				{
					auto center = view.getCenter();
					center.x -= 15;
					view.setCenter(center);
				}

				if (keyReleased->code == sf::Keyboard::Key::Right)
				{
					auto center = view.getCenter();
					center.x += 15;
					view.setCenter(center);
				}

				window.setView(view);
			}
			else if (const auto* scrolled = event->getIf<sf::Event::MouseWheelScrolled>())
			{
				if (scrolled->wheel == sf::Mouse::Wheel::Vertical)
				{
					// Handle vertical wheel scrolling
					std::cout << "Wheel scroll delta : " << scrolled->delta << std::endl;

					if (scrolled->delta != 0)
					{
						view.zoom(1.0F - (scrolled->delta / 5));
						window.setView(view);
					}
				}
			}
		}

		// Graphical Region
		window.clear(sf::Color::White);

		window.draw(background);
		window.draw(center_mark);

		// Window Display
		window.display();
	}
}
