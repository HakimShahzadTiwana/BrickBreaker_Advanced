#include "Paddle.h"

sf::Texture Paddle::texture;

Paddle::Paddle(std::string PathToImg)
{
	texture.loadFromFile(PathToImg);

	sprite.setTexture(texture);
	
	sf::Vector2u TexSize = texture.getSize();

	sprite.setOrigin(getCenter());
	sprite.setScale({ GameProperties::PaddleWidth / TexSize.x, GameProperties::PaddleHeight / TexSize.y });
	
	float yPos = WindowProperties::Hieght - getBoundingBox().height / 2;
	float xPos = WindowProperties::Width / 2.0f;
	startingPosition = { xPos,yPos };
	sprite.move(startingPosition);

	velocity = { GameProperties::PaddleSpeed,0 };

	
}

void Paddle::processPlayerInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		if (getPosition().x > getBoundingBox().width / 2)
			move_left();
		else
			velocity.x = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		if (getPosition().x + getBoundingBox().width/2 < WindowProperties::Width)
			move_right();
		else
			velocity.x = 0;
	}
	else
	{
		velocity.x = 0;
	}
}

void Paddle::update()
{
	processPlayerInput();
	sprite.move(velocity);

}

void Paddle::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Paddle::resetPosition()
{
	sprite.setPosition(startingPosition);
}

void Paddle::move_up()
{
	// Do nothing, paddle soesnt move up
}

void Paddle::move_right()
{
	velocity.x = GameProperties::PaddleSpeed;
}
void Paddle::move_down()
{
	// Do nothing, paddle doesnt move down
}
void Paddle::move_left()
{
	velocity.x = -GameProperties::PaddleSpeed;
}

