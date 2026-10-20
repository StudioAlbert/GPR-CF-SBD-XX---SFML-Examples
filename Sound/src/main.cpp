// Sound : une musique en flux, deux effets, et un seul sf::Sound dont on change le buffer.

#include <iostream>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "The Game");

    // Musique
    float volume = 50;

    sf::Music music;
    if (!music.openFromFile("data/sounds/music.wav"))
        return EXIT_FAILURE;
    music.setLooping(true);

    // Sound FX
    sf::SoundBuffer soundFx1;
    sf::SoundBuffer soundFx2;

    if (!soundFx1.loadFromFile("data/sounds/soundFx_Laser.wav"))
        return EXIT_FAILURE;
    if (!soundFx2.loadFromFile("data/sounds/soundFx_Ring.wav"))
        return EXIT_FAILURE;

    // En SFML 3 un son ne vit pas sans buffer : il en faut un des la construction.
    sf::Sound sound(soundFx1);

    // Basic Setup of the window
    // Vertical sync, framerate
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        while (const std::optional event = window.pollEvent())
        {
            volume = music.getVolume();

            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                // Test de la valeur de la touche
                std::cout << "Key pressed : " << static_cast<int>(keyPressed->code) << std::endl;

                switch (keyPressed->code)
                {
                case sf::Keyboard::Key::Up:

                    volume += 10;
                    if (volume >= 100)
                        volume = 100;

                    std::cout << "Volume UP ^^^^^^^^^^^^^^^^^^^^^^^^^^^^ " << volume << std::endl;
                    break;

                case sf::Keyboard::Key::Down:

                    volume -= 10;
                    if (volume <= 0)
                        volume = 0;
                    music.setVolume(volume);

                    std::cout << "Volume DOWN vvvvvvvvvvvvvvvvvvvvvvvvvvv " << volume << std::endl;
                    break;

                case sf::Keyboard::Key::Space:
                    std::cout << "PLAY / PAUSE !!!!!!!!!!!!!!!!!!!" << std::endl;
                    if (music.getStatus() != sf::Music::Status::Playing) {
                        music.play();
                    }
                    else {
                        music.pause();
                    }
                    std::cout << "Is playing ??? " << static_cast<int>(music.getStatus());
                    break;

                case sf::Keyboard::Key::X:
                    if (keyPressed->shift) {
                        std::cout << "Tiouuuuu ***************************" << std::endl;
                        sound.setBuffer(soundFx1);
                    }
                    else {
                        std::cout << "Driiing ***************************" << std::endl;
                        sound.setBuffer(soundFx2);
                    }

                    sound.play();
                    break;

                default:
                    break;
                }
            }
        }

        // Graphical Region
        window.clear(sf::Color::Black);

        music.setVolume(volume);
        sound.setVolume(volume);

        // Window Display
        window.display();
    }
}
