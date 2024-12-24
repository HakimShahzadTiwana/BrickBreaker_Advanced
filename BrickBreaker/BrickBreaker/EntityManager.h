#pragma once
#include "Entity.h"

// Alias for vector of unique pointers pointing to entities
using entity_vector = std::vector<std::unique_ptr<Entity>>;

// Alias for vector of raw pointers that dont have ownership pointing to entities
using entity_alias_vector = std::vector<Entity*>;

// Alias for map of entites where key is the hash of the class type and value is raw pointers pointing to entities
using entity_map = std::map<size_t, entity_alias_vector>;

class EntityManager
{
	 entity_vector allEntities;
	 entity_map grouped_entities;

public:

	// Creates an object of an Entity type to keep track of them
	template<typename T, typename... Args>
	T& create(Args&&... args);

	// Scans and cleans up destroyed entities
	void refresh();

	// Destroy all entities
	void clear();
	
	// Updates all enitites
	void update();

	// Draws all entities
	void draw(sf::RenderWindow& window);

	// Get all entities of a specific type
	template<typename T>
	entity_alias_vector& getAllOfType();


	// Applies a specific function to all entities of a specific type
	template<typename T, typename Func>
	void applyAll(const Func& func);

	
	
	

};


#pragma region Template Definitions

// Template function to create entities. Make sure type is of entity.
template<typename T, typename... Args>
T& EntityManager::create(Args&&... args)
{
	// This function should only work for classes based of the Entity class
	static_assert(std::is_base_of<Entity, T>::value, R"("T" type parameter in create() must be derived from "Entity")");

	// Create the unique_ptr to the entity 
	// forward the arguements to the entities constructor
	auto ptr{ std::make_unique<T>(std::forward<Args>(args)...) };

	// Create an alias for the pointer 
	auto ptr_alias = ptr.get();

	// Create a hash code from the type of the object to use in the map as a key
	auto hash = typeid(T).hash_code();

	// Insert alias pointer into the map
	grouped_entities[hash].emplace_back(ptr_alias);

	// Move the unique pointer into the vector
	allEntities.emplace_back(std::move(ptr));

	return *ptr_alias;
}

// Template function to get all entities of a specific type
template<typename T>
entity_alias_vector& EntityManager::getAllOfType() 
{
	return grouped_entities[typeid(T).hash_code()];
}


// Template function to apply a specific function to all entities of a specific type
template<typename T, typename Func>
void EntityManager::applyAll(const Func& func) 
{
	// Get all entities of specified type
	entity_alias_vector& targetEntities{ getAllOfType<T>() };

	for (auto ptr : targetEntities) 
	{
		// Cast pointer of base class to derived type and derefence to get the object
		func(*dynamic_cast<T*>(ptr));
	}

}


#pragma endregion

