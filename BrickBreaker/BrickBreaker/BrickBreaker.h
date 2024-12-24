#pragma once
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Background.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "EntityManager.h"
#include "GameSettings.h"


class BrickBreaker
{
	EntityManager entityManager;

	sf::RenderWindow gameWindow{ {WindowProperties::Width,WindowProperties::Hieght},"Welcome to BrickBreaker" };

	GameState gameState{ GameState::paused };

	int currentLives{ GameProperties::PlayerLives };

	sf::Font font;
	sf::Text txtState, txtLives, txtHelp;
	
	
public:

	BrickBreaker();

	void run();
	void reset();

private:

	bool isPauseKeyPressed{ false };
	void HandleKeyBoardEvents();
	void HandleWindowEvents();


};

void handleCollision(Ball& ball, const Paddle& paddle);
void handleCollision(Ball& ball, Brick& brick);


