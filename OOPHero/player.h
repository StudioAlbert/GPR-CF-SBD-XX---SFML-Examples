#pragma once

#include <optional>

#include <SFML/Graphics.hpp>

constexpr float speed = 5.f;

class Player : public sf::Drawable, public sf::Transformable
{
	// Les textures passent par le constructeur : en SFML 3, charger peut echouer,
	// et un sprite ne vit pas sans texture.
	sf::Texture linkUp, linkDown, linkLeft, linkRight;
	sf::Sprite sprite;

public:
	Player()
		: linkUp("data/sprites/ZeldaUp.png"),
		  linkDown("data/sprites/ZeldaDown.png"),
		  linkLeft("data/sprites/ZeldaLeft.png"),
		  linkRight("data/sprites/ZeldaRight.png"),
		  sprite(linkUp)
	{
		sprite.setTextureRect({ {0,0}, {32,32} });
	}

	void HandleEvent(const std::optional<sf::Event>& event)
	{
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{

			if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
			{
				move({ 0, speed });
				sprite.setTexture(linkDown);
			}
			if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
			{
				move({ 0, -speed });
				sprite.setTexture(linkUp);
			}
			if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
			{
				move({ -speed, 0 });
				sprite.setTexture(linkLeft);
			}
			if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
				move({ speed, 0 });
				sprite.setTexture(linkRight);
			}

		}
	}

	void Update()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
		{
			move({ 0, speed });
			sprite.setTexture(linkDown);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
		{
			move({ 0, -speed });
			sprite.setTexture(linkUp);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
		{
			move({ -speed , 0});
			sprite.setTexture(linkLeft);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
		{
			move({ speed , 0 });
			sprite.setTexture(linkRight);
		}
	}

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.transform *= getTransform();

		target.draw(sprite, states);
	}

};
