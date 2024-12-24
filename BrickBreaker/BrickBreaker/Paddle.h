#pragma once
#include "MovingEntity.h"
#include "GameSettings.h"

class Paddle : public MovingEntity
{
	static sf::Texture texture;
	sf::Vector2f startingPosition;

public:

	Paddle(std::string PathToImg);

	void update() override;
	void draw(sf::RenderWindow& window) override;

	void resetPosition();
	void move_up() override;
	void move_left() override;
	void move_right() override;
	void move_down() override;

private:
	void processPlayerInput();
};

