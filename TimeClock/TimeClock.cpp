// TimeClock : l'horloge SFML, le temps ecoule et la remise a zero.

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

constexpr float shootInterval = 1.0f;

int main()
{
	sf::Clock clock_;
	sf::Time time_ = clock_.getElapsedTime();
	float seconds = time_.asSeconds();

	time_ += clock_.restart();
	if (time_.asSeconds() > shootInterval)
	{
		// Shhhhhhoooooooooooooooooooooooooooooot !
		time_ = sf::Time::Zero;
	}
}
