#include "Animation.hpp"

#include <filesystem>
#include <iostream>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Time.hpp>

bool Animation::Load(std::string folder)
{
	// Controle que le repertoire contient des textures
	if (std::filesystem::is_empty(folder))
	{
		return false;
	}

	// Création de la texture par défaut
	const sf::Image image({100, 100}, sf::Color::Magenta);
	if (!defaultTexture_.loadFromImage(image))
	{
		return false;
	}

	// Load every textures--------------------------------------------------------------------------------------------------
	for (const auto& file : std::filesystem::directory_iterator(folder))
	{
		std::cout << file.path() << std::endl;

		if (file.path().extension() != ".png")
		{
			std::cout << "Wrong file extension.\n";
			textures_.clear();
			return false;
		}

		textures_.emplace_back(file.path());
	}

	return true;
}

void Animation::UpdateIdx()
{
	sf::Time elapsed = clock_.restart();
	totalElapsed_ = totalElapsed_ + elapsed;
	std::cout << std::endl << "Counting ..... " << totalElapsed_.asSeconds() << std::endl;

	if (totalElapsed_.asSeconds() >= floatPeriod) {
		// Picking next texture
		idxTextures_++;
		// Reset time
		totalElapsed_ = sf::Time::Zero;
		// Switch to first frame
		if (idxTextures_ >= textures_.size())
		{
			idxTextures_ = 0;
		}
		std::cout << "New texture index : " << idxTextures_ << std::endl;
	}
}

const sf::Texture* Animation::Get()
{
	// Every 100ms, we load a new texture
	if (isPlaying_) {
		UpdateIdx();
	}

	if (!textures_.empty())
	{
		return &textures_[idxTextures_];
	}

	return &defaultTexture_;
}

void Animation::Play()
{
	isPlaying_ = true;
}

void Animation::Pause()
{
	isPlaying_ = false;
}

bool Animation::IsPlaying() const
{
	return isPlaying_;
}
