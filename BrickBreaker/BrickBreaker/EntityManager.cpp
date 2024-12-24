#include "EntityManager.h"

void EntityManager::refresh()
{
	// First remove all the alias pointers in the grouped entities
	// Doing this after removing pointers from allEntities will result in dangling pointers since allEntities has ownership
	for (auto& [type, aliasVector] : grouped_entities) 
	{
		aliasVector.erase(std::remove_if(std::begin(aliasVector), std::end(aliasVector), [](auto entity) {return entity->getIsDestroyed(); }), std::end(aliasVector));
	}

	// Now we can safely destroy the pointers (managed by the unique_ptrs) since all aliases have now been removed
	allEntities.erase(std::remove_if(std::begin(allEntities), std::end(allEntities), [](const auto& entity) {return entity->getIsDestroyed(); }), std::end(allEntities));

}

void EntityManager::clear()
{
	// make sure to clear aliases first before destorying pointers (handled by the unique ptrs)
	grouped_entities.clear();
	allEntities.clear();
}

void EntityManager::update()
{
	for (auto& entities : allEntities) 
	{
		entities->update();
	}
}

void EntityManager::draw(sf::RenderWindow& window)
{
	for (auto& entities : allEntities)
	{
		entities->draw(window);
	}
}



