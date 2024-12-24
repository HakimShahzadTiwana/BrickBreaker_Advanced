#include "Entity.h"

sf::FloatRect Entity::getBoundingBox() const noexcept
{
    return sprite.getGlobalBounds();
}

sf::Vector2f Entity::getCenter() const noexcept
{
    sf::FloatRect bounds = getBoundingBox();

    return {bounds.width/2.0f,bounds.height/2.0f};
}

sf::Vector2f Entity::getPosition() const noexcept
{
    return sprite.getPosition();
}

void Entity::Destroy()
{
    bIsDestroyed = true;
}

bool Entity::getIsDestroyed() const noexcept
{
    return bIsDestroyed;
}

float Entity::getLeftEdge()
{
    auto box = getBoundingBox();
    return getPosition().x - box.width / 2.0f;
}

float Entity::getRightEdge()
{
    auto box = getBoundingBox();
    return getPosition().x + box.width / 2.0f;
}

float Entity::getTopEdge()
{
    auto box = getBoundingBox();
    return getPosition().y - box.height / 2.0f;
}

float Entity::getBottomEdge()
{
    auto box = getBoundingBox();
    return getPosition().y + box.height / 2.0f;
}






// Global functions 
bool isInteracting(const Entity& e1, const Entity& e2)
{
    auto box1 = e1.getBoundingBox();
    auto box2 = e2.getBoundingBox();
    return box1.intersects(box2);
}
