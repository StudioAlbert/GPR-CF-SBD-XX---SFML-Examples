// Events-a : la boucle d'evenements, le focus et le redimensionnement.

#include <iostream>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML First Window");

    sf::CircleShape penta(50.0f, 5);
    penta.setOrigin({penta.getRadius(), penta.getRadius()});
    penta.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});

    sf::Color backgroundColor(sf::Color::Blue);

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
            else if (event->is<sf::Event::FocusLost>())
            {
                backgroundColor = sf::Color(50, 0, 0);
            }
            else if (event->is<sf::Event::FocusGained>())
            {
                backgroundColor = sf::Color::Blue;
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                // la vue garde le repere en pixels : un pixel de la fenetre = une unite du monde
                const sf::Vector2f visibleSize(resized->size);
                window.setView(sf::View(sf::FloatRect({0.0f, 0.0f}, visibleSize)));
                penta.setPosition(visibleSize / 2.0f);
            }
        }

        window.draw(penta);

        // effacement les tampons de couleur/profondeur
        window.display();
    }

    return EXIT_SUCCESS;
}
