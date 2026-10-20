

#include <iostream>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "The Game");

	// Musique
	bool playPauseMusic = false;
	float volume = 50;

	sf::Music music;
	if (!music.openFromFile("data/sounds/music.wav"))
		return -1;
	music.setLooping(true);
	music.play();
	music.stop();
	music.pause();
	music.setVolume(30);


	// Sound FX
	sf::SoundBuffer buffSoundFxLaser;
	sf::SoundBuffer buffSoundFxRing;

	if (!buffSoundFxLaser.loadFromFile("data/sounds/soundFx_Laser.wav"))
		return -1;
	if (!buffSoundFxRing.loadFromFile("data/sounds/soundFx_Ring.wav"))
		return -1;

	sf::Sound soundLaser(buffSoundFxLaser);
	sf::Sound soundRing(buffSoundFxRing);

	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

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
				// Test de la valeur de la touche
				std::cout << "Key pressed : " << static_cast<int>(keyPressed->code) << std::endl;

				if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
				{
					volume += 10;
					if (volume >= 100)
						volume = 100;

					std::cout << "Volume UP ^^^^^^^^^^^^^^^^^^^^^^^^^^^^ " << volume << std::endl;
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
				{
					volume -= 10;
					if (volume <= 0)
						volume = 0;
					music.setVolume(volume);
					soundLaser.setVolume(volume);
					soundRing.setVolume(volume);

					std::cout << "Volume DOWN vvvvvvvvvvvvvvvvvvvvvvvvvvv " << volume << std::endl;
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
				{
					std::cout << "PLAY / PAUSE !!!!!!!!!!!!!!!!!!!" << std::endl;
					if (music.getStatus() != sf::Music::Status::Playing) {
						music.play();
					}
					else {
						music.pause();
					}
					std::cout << "Is playing ??? " << static_cast<int>(music.getStatus());
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::X)
				{
					if (keyPressed->shift) {
						std::cout << "Tiouuuuu **************	*************" << std::endl;
						//sound.setBuffer(soundFx_Laser);
						soundLaser.play();
					}
					else {
						std::cout << "Driiing ***************************" << std::endl;
						//sound.setBuffer(soundFx_Ring);
						soundRing.play();
					}

					
				}
			}
			
		}
	}

	// Graphical Region
	window.clear(sf::Color::Black);


	// Window Display
	window.display();

}
