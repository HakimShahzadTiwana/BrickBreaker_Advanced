#pragma once
#include <SFML/Graphics.hpp>

// Abstract base class to represent any graphical entity on the string
class Entity
{

protected:
	sf::Sprite sprite;

	bool bIsDestroyed = false;

public:

	// Updates properties of the entity i.e position,appearence etc.
	virtual void update() = 0;

	// Draw updated entity to the screen
	virtual void draw(sf::RenderWindow& window) = 0;

	// Gets the bounding box of the sprite
	sf::FloatRect getBoundingBox() const noexcept;
	
	// Gets the center of the sprite.
	sf::Vector2f getCenter() const noexcept;

	// Gets position of sprite
	sf::Vector2f getPosition() const noexcept;

	// Destroy the entity
	void Destroy();

	// returns if the entity has been marked as destroyed
	bool getIsDestroyed() const noexcept;

	// Get edges of the sprite
	float getLeftEdge();
	float getRightEdge();
	float getTopEdge();
	float getBottomEdge();



	// Virtual destructor (since we are using virtual functions we need to provide a virtual destructor)
	virtual ~Entity() {};

};

bool isInteracting(const Entity& e1, const Entity& e2);

