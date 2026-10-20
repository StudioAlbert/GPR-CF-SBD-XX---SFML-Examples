#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "enemy.hpp"
#include "projectile.hpp"

class EntityManager : public sf::Drawable
{

public:
	virtual void SpawnEntity(sf::Vector2f) = 0;
	void Update(const sf::RenderWindow&, float dt);
	std::vector<AutoEntity*>&  GetEntities();

protected:
	std::vector<AutoEntity*> entities_;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

class EnemyManager : public EntityManager
{

public:
	void SpawnEntity(sf::Vector2f position) override
	{
		// Ajouter dans le vecteur
		entities_.emplace_back(new Enemy());

		// mettre à la position de spawn
		entities_.back()->Load();
		entities_.back()->SetPosition(position);
	}

};

class ProjectileManager : public EntityManager
{

public:
	void SpawnEntity(sf::Vector2f position) override
	{
		// Ajouter dans le vecteur
		entities_.emplace_back(new Projectile());

		// mettre à la position de spawn
		entities_.back()->Load();
		entities_.back()->SetPosition(position);
	}
};

