#include "Brick.h"

texture_vec Brick::variantTextures;

Brick::Brick(float x, float y)
{
	if (variantTextures.empty())
	{
		for (auto path : getBrickVariantTextures())
		{
			auto tex = std::make_unique<sf::Texture>();
			if (!tex->loadFromFile(path))
			{
				std::cout << "Could not load file " << path << std::endl;
				return;
			}

			variantTextures.push_back(std::move(tex));
		}
	}

	strength = variantTextures.size();
	setSpriteTexture(*variantTextures[strength - 1].get());

	sprite.setPosition({ x,y });
	sprite.setOrigin(getCenter());

}

void Brick::setStrength(int s) noexcept
{
	strength = s;
}

void Brick::weakenBrick() noexcept
{
	--strength;
	if (!isTooWeak()) 
	{
		setSpriteTexture(*variantTextures[strength - 1].get());
	}
}

bool Brick::isTooWeak() const noexcept
{
	return strength <= 0;
}


void Brick::update()
{


}

void Brick::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

std::vector<std::string> Brick::getBrickVariantTextures()
{

	std::vector<std::string> variantTexturePaths;
	try {
		for (const auto& entry : fs::directory_iterator(BrickVariantDirectory)) {
			variantTexturePaths.push_back(entry.path().generic_string());
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return variantTexturePaths;
	
}

void Brick::setSpriteTexture(const sf::Texture& tex)
{
	sprite.setTexture(tex);
	sf::Vector2u TexSize = tex.getSize();
	sprite.setScale({ GameProperties::BrickWidth / TexSize.x, GameProperties::BrickHeight / TexSize.y });
}
