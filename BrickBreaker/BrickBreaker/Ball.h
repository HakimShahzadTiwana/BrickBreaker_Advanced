#pragma once
#include <string>
#include "MovingEntity.h"
#include "GameSettings.h"

class Ball : public MovingEntity
{
	static sf::Texture texture;
public:

	// x,y position on screen;
	Ball(float x, float y, std::string PathToImg);

	void update() override;
	void draw(sf::RenderWindow& window) override;

	void move_up() override;
	void move_right() override;
	void move_left() override;
	void move_down() override;
};

