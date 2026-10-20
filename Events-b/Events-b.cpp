// Events-b : la souris, le lissage de position et le nombre de sommets.

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


int main()
{
    // Setup
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML First Window");
    window.setFramerateLimit(30);

    sf::CircleShape penta(50.0f, 5);
    penta.setOrigin({penta.getRadius() / 2.0f, penta.getRadius() / 2.0f});
    penta.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});

    // FOLLOW THE MOUSE
    sf::Vector2f position = penta.getPosition();

    sf::Color backgroundColor(sf::Color::Red);

    while (window.isOpen())
    {
        window.clear(backgroundColor);

        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        while (const std::optional event = window.pollEvent())
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                position = sf::Vector2f(mouseMoved->position);
                // Option A : Follow the mouse
                //penta.setPosition(position);
            }
            else if (event->is<sf::Event::MouseButtonReleased>())
            {
                // CHANGE THE SHAPE
                const auto newPointCount = static_cast<std::size_t>(3 + 5 * ((rand() % 100) / 100.0f));
                penta.setPointCount(newPointCount);
            }
        }

        // -------------------------------------------------------------------------------------------------
        // Option B: avec un petit décalage pour faire joli
        const float smoothRatio = 0.9f;
        penta.setPosition(smoothRatio * penta.getPosition() + (1.0f - smoothRatio) * position);

        window.draw(penta);

        // effacement les tampons de couleur/profondeur
        window.display();
    }

    return EXIT_SUCCESS;
}
