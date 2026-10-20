#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>

#include "entity_manager.hpp"
#include "auto_entity.hpp"
#include "motor.h"

class StarshipPlayer : public sf::Drawable
{

	sf::Texture texture;
	sf::RectangleShape rect_;

	Motor motor_;

	ProjectileManager projectileManager;


public:
	void Load(sf::Vector2f);
	void Update(sf::RenderWindow&, float);
	bool CheckCollisions(std::vector<AutoEntity*>& others);
	void CheckProjectileCollisions(std::vector<AutoEntity*>& others);
	void HandleEvent();

	void SetPosition(sf::Vector2f);

protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

};

