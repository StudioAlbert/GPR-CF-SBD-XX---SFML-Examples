#include "starship_player.hpp"

#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

void StarshipPlayer::Load(sf::Vector2f spawnPosition)
{
	if (!texture.loadFromFile("data/sprites/playerShip3_red.png"))
		std::cerr << "Texture introuvable : data/sprites/playerShip3_red.png\n";

	motor_.SetPosition(spawnPosition);
	motor_.SetDirection({ 0, 1 });
	motor_.SetSpeed(600);

	rect_.setTexture(&texture);
	rect_.setSize({ static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y)});

}

void StarshipPlayer::Update(sf::RenderWindow& window, float dt)
{

	rect_.setPosition(motor_.Move(dt));

	projectileManager.Update(window, dt);

}

bool StarshipPlayer::CheckCollisions(std::vector<AutoEntity*>& others)
{

	for (auto& other : others) {

		if (other->StillAlive == false)
		{
			continue;
		}

		if (rect_.getGlobalBounds().findIntersection(other->GetBounds()))
		{
			other->StillAlive = false;
			return true;
		}
	}

	return false;

}

void StarshipPlayer::CheckProjectileCollisions(std::vector<AutoEntity*>& others)
{

	auto bullets = projectileManager.GetEntities();

	for (auto& bullet : bullets)
	{
		if (!bullet->StillAlive)
		{
			continue;
		}

		for (auto & other : others)
		{

			if (!other->StillAlive)
			{
				continue;
			}

			if (bullet->GetBounds().findIntersection(other->GetBounds()))
			{
				other->StillAlive = false;
				bullet->StillAlive = false;
			}
		}
	}


}

void StarshipPlayer::HandleEvent()
{

	sf::Vector2f direction = {0,0};

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
	{
		direction.y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
	{
		direction.y = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
	{
		direction.x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
		direction.x = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)){
		projectileManager.SpawnEntity(rect_.getPosition());
	}

	motor_.SetDirection(direction);
}

void StarshipPlayer::SetPosition(sf::Vector2f position)
{
	motor_.SetPosition(position);
}

void StarshipPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//sf::Sprite sprite(texture);
	target.draw(rect_);
	target.draw(projectileManager);

}



