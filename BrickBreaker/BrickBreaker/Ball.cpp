#include "Ball.h"
#include <iostream>
// Init static member 

sf::Texture Ball::texture;

Ball::Ball(float x, float y,std::string PathToImg)
{
	// Load image and set sprite
	texture.loadFromFile(PathToImg);

	// Set Sprite Texture
	sprite.setTexture(texture);

	// Set sprite scale
	sf::Vector2u TexSize = texture.getSize();
	sprite.scale({ GameProperties::BallSize / TexSize.x, GameProperties::BallSize / TexSize.y });

	// Init position and velocity
	sprite.setPosition(x, y);
	velocity = { GameProperties::BallSpeed,GameProperties::BallSpeed }; 
}

void Ball::update()
{
	// Move the position of the sprite 
	sprite.move(velocity);

	// Change directions if at the edge of the screen

	if (getPosition().x < 0 || getPosition().x > WindowProperties::Width)
		velocity.x = -velocity.x;

	if (getPosition().y < 0) 
		velocity.y = -velocity.y;

	// if ball reaches bottom of the screen
	if (getPosition().y > WindowProperties::Hieght)
	{
		Destroy();
	}

	
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Ball::move_up()
{
	velocity.y = -GameProperties::BallSpeed;
}

void Ball::move_right()
{
	velocity.x = GameProperties::BallSpeed;
}

void Ball::move_left()
{
	velocity.x = -GameProperties::BallSpeed;
}

void Ball::move_down()
{
	velocity.y = GameProperties::BallSpeed;
}
