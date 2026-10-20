#pragma once

#include <string_view>

#include <SFML/Graphics.hpp>
#include "motor.h"

class AutoEntity : public sf::Drawable
{

	sf::Texture texture;
	
	
protected:
	Motor motor_;
	sf::RectangleShape rect_;
	void Load(std::string_view, sf::Vector2f, float);


public:
	void SetPosition(sf::Vector2f);
	sf::Vector2f GetPosition();

	virtual void Move(float) = 0;
	virtual void Load() = 0;
	sf::FloatRect GetBounds();

	bool StillAlive = true;

protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

};

