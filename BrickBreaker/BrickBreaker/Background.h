#pragma once
#include "Entity.h"


class Background : public Entity
{
	static sf::Texture texture;
public:

	// x,y - size of screen 
	Background(float x, float y, std::string PathToImg);

	void update() override;
	void draw(sf::RenderWindow& window) override;

};

