#pragma once

#include "auto_entity.hpp"

class Projectile : public AutoEntity
{

public:
	void Move(float) override;
	void Load() override;
};

inline void Projectile::Move(float dt)
{
	rect_.setPosition(motor_.Move(dt));
}

inline void Projectile::Load()
{
	AutoEntity::Load("data/sprites/laserBlue01.png", { 0, -1 }, 600);
}



