#pragma once
#include "Entity.h"

// Abstract class for moving entities
class MovingEntity : public Entity
{
protected:
	sf::Vector2f velocity;

	virtual void move_up() = 0;
	virtual void move_right() = 0;
	virtual void move_left() = 0;
	virtual void move_down() = 0;
};

