#pragma once

#include "auto_entity.hpp"

class Enemy : public AutoEntity
{
public :
	void Load() override;
	void Move(float) override;

};

inline void Enemy::Move(float dt)
{
	rect_.setPosition(motor_.Move(dt));
}

inline void Enemy::Load()
{
	AutoEntity::Load("data/sprites/enemyBlack4.png", { 0, 1 }, 300);
}


