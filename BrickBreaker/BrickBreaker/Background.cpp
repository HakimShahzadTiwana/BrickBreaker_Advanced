#include "Background.h"
// Init static member
sf::Texture Background::texture;

Background::Background(float x, float y, std::string PathToImg)
{
	// Load Texture
	texture.loadFromFile(PathToImg);
	
	// Set texture for the sprite 
	sprite.setTexture(texture);
	
	// Scale the sprite to the size of the screen
	sf::Vector2u texSize = texture.getSize();
	sprite.setScale({ x / texSize.x,y / texSize.y });

	// Init sprite position
	sprite.setPosition(0, 0);
}

void Background::update() 
{
	// Background doesnt need to be updated
}

void Background::draw(sf::RenderWindow& window) 
{
	// Draw the sprite into the buffer 
	window.draw(sprite);
}
