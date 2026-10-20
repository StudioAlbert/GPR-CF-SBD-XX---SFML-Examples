#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

constexpr float floatPeriod = 1.0f / 10.0f;

class Animation
{
private:
	std::vector<sf::Texture> textures_;
	std::size_t idxTextures_ = 0;

	sf::Clock clock_;
	sf::Time totalElapsed_;

	bool isPlaying_ = true;

	sf::Texture defaultTexture_;

	void UpdateIdx();

public:
	bool Load(std::string folder);

	void Play();
	void Pause();

	const sf::Texture* Get();
	bool IsPlaying() const;

};
