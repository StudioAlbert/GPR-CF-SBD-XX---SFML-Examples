// AnimationClass : la meme animation, mais rangee dans une classe.

#include <iostream>

#include <SFML/System/Vector2.hpp>

#include "Animation.hpp"
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"


constexpr sf::Vector2f kCharacterSize(100, 100);


int main()
{
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "The Game");

    sf::RectangleShape character(kCharacterSize);
    Animation anim;

    // Basic Setup of the window
    // Vertical sync, framerate
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);

    if (!anim.Load("data/sprites/character"))
        return EXIT_FAILURE;

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
            else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                if (keyReleased->scancode == sf::Keyboard::Scancode::Space)
                {
	                if (anim.IsPlaying())
	                {
                        anim.Pause();
	                }else
	                {
                        anim.Play();
	                }
                }
            }
        }

        character.setTexture(anim.Get());

        // Graphical Region
        window.clear(sf::Color::Black);

        window.draw(character);

        // Window Display
        window.display();
    }
}
