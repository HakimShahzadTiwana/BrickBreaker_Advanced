#pragma once

#include <filesystem>
#include <iostream>

#include "Entity.h"
#include "GameSettings.h"

namespace fs = std::filesystem;
using texture_vec = std::vector<std::unique_ptr<sf::Texture>>;
class Brick : public Entity
{
	static texture_vec variantTextures;

	int strength;

public:
	Brick(float x,float y);

	void setStrength(int s) noexcept;
	void weakenBrick() noexcept;
	bool isTooWeak() const noexcept;

	void update();
	void draw(sf::RenderWindow& window);

private:

	std::string BrickVariantDirectory = "./Textures/Bricks";
	std::vector<std::string> getBrickVariantTextures();
	void setSpriteTexture(const sf::Texture& tex);
};

