#include "BrickBreaker.h"


void handleCollision(Ball& ball, const Paddle& paddle)
{
	if (isInteracting(ball, paddle))
	{
		ball.move_up();

		if (ball.getPosition().x < paddle.getPosition().x)
			ball.move_left();
		else
			ball.move_right();
	}
}

void handleCollision(Ball& ball, Brick& brick)
{
	// Check if ball is overlapping with brick
	if (isInteracting(ball, brick)) 
	{
		
		// Check for overlaps
		float leftOverlap = ball.getRightEdge() - brick.getLeftEdge();
		float rightOverlap = ball.getLeftEdge() - brick.getRightEdge();
		float topOverlap = ball.getBottomEdge() - brick.getTopEdge();
		float bottomOverlap = ball.getTopEdge() - brick.getBottomEdge();

		// Find out what side the ball collided with the brick
		bool fromLeft = std::abs(leftOverlap) < std::abs(rightOverlap);
		bool fromTop = std::abs(topOverlap) < std::abs(bottomOverlap);

		// Get the overlap values from the sides
		float minXOverlap = fromLeft ? leftOverlap : rightOverlap;
		float minYOverlap = fromTop ? topOverlap : bottomOverlap;

		// Check if the ball collided with the side edges or the top and bottom edges
		if (std::abs(minXOverlap) < std::abs(minYOverlap)) 
		{
			if (fromLeft) 
			{
				ball.move_right();
			}
			else 
			{
				ball.move_left();
			}
		}
		else 
		{
			if (fromTop) 
			{
				ball.move_up();
			}
			else 
			{
				ball.move_down();
			}
		}

		brick.weakenBrick();
		if (brick.isTooWeak()) 
		{
			// Destroy brick
			brick.Destroy();
		}
		
	}
}

BrickBreaker::BrickBreaker()
{

	font.loadFromFile("Fonts/ALGER.TTF");

	txtState.setFont(font);
	txtState.setPosition(WindowProperties::Width / 2-54, WindowProperties::Hieght / 2+30);
	txtState.setCharacterSize(35);
	txtState.setFillColor(sf::Color::White);
	txtState.setString("Paused");

	txtHelp.setFont(font);
	txtHelp.setPosition(WindowProperties::Width / 2 - 75.0f, WindowProperties::Hieght / 2 + 70);
	txtHelp.setCharacterSize(20);
	txtHelp.setFillColor(sf::Color::White);
	txtHelp.setString("Space to Play");

	txtLives.setFont(font);
	txtLives.setPosition(WindowProperties::Width - 80, WindowProperties::Hieght-30);
	txtLives.setCharacterSize(15);
	txtLives.setFillColor(sf::Color::Red);
	txtLives.setString("Lives : " + std::to_string(currentLives));

	entityManager.clear();

	entityManager.create<Background>(WindowProperties::Width, WindowProperties::Hieght, "Textures/Background/background.jpg");
	entityManager.create<Ball>(WindowProperties::Width / 2, WindowProperties::Hieght / 2, "Textures/Ball/Ball_Blue.png");
	entityManager.create<Paddle>("Textures/Paddle/Paddle.png");

	for (int i = 0; i < GameProperties::BrickCols; ++i)
	{
		for (int j = 0; j < GameProperties::BrickRows; ++j)
		{
			float posX = GameProperties::BrickStartOffset + (i + 1) * GameProperties::BrickWidth;
			float posY = GameProperties::BrickHeight * (j + 1);
			entityManager.create<Brick>(posX, posY);
		}
	}
	
	// Set a frame rate limit for the window
	gameWindow.setFramerateLimit(WindowProperties::FrameRate);
}

void BrickBreaker::run()
{
	
	// Game loop 
	while (gameWindow.isOpen())
	{
		// Clear window
		gameWindow.clear(sf::Color::Black);

		HandleWindowEvents();
		HandleKeyBoardEvents();
	

		if (gameState == GameState::running) 
		{
			entityManager.update();

			if (entityManager.getAllOfType<Ball>().empty())
			{
				entityManager.create<Ball>(WindowProperties::Width / 2, WindowProperties::Hieght / 2, "Textures/Ball/Ball_Blue.png");
				entityManager.applyAll<Paddle>([](auto& paddle) {paddle.resetPosition(); });
				--currentLives;
				txtLives.setString("Lives : " + std::to_string(currentLives));

				if (currentLives <= 0) 
				{
					gameState = GameState::gameOver;
					txtState.setString("Game Over");
					txtHelp.setString("Fucking Loser");
				}
				else 
				{
					gameState = GameState::paused;
					txtState.setString("Paused");
					txtHelp.setString("Space to Play");
				}
			}

			// Handle collisions with balls and bricks
			entityManager.applyAll<Ball>([this](auto& ball) 
			{
				entityManager.applyAll<Brick>([&ball](auto& brick)
				{
					handleCollision(ball, brick);
				});
			});

			// Handle collisions with balls and paddles
			entityManager.applyAll<Ball>([this](auto& ball) 
			{
				entityManager.applyAll<Paddle>([&ball](auto& paddle)
				{
					handleCollision(ball, paddle);
				});
			});
			
			entityManager.refresh();

			if (entityManager.getAllOfType<Brick>().empty()) 
			{
				gameState = GameState::gameWon;
				txtState.setString("You win");
				txtHelp.setString("This is all you'll ever achieve in life");
			}

		}
		
		// Update graphics buffer
		entityManager.draw(gameWindow);
		gameWindow.draw(txtState);
		gameWindow.draw(txtHelp);
		gameWindow.draw(txtLives);

		//Display Buffer in Window
		gameWindow.display();

	}
}

void BrickBreaker::reset()
{

	entityManager.clear();

	entityManager.create<Background>(WindowProperties::Width, WindowProperties::Hieght, "Textures/Background/background.jpg");
	entityManager.create<Ball>(WindowProperties::Width / 2, WindowProperties::Hieght / 2, "Textures/Ball/Ball_Blue.png");
	entityManager.create<Paddle>("Textures/Paddle/Paddle.png");

	for (int i = 0; i < GameProperties::BrickCols; ++i)
	{
		for (int j = 0; j < GameProperties::BrickRows; ++j)
		{
			float posX = GameProperties::BrickStartOffset + (i + 1) * GameProperties::BrickWidth;
			float posY = GameProperties::BrickHeight * (j + 1);
			entityManager.create<Brick>(posX, posY);
		}
	}

	currentLives = GameProperties::PlayerLives;
	gameState = GameState::paused;

}

void BrickBreaker::HandleKeyBoardEvents()
{
	// Exit on escape key
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		gameWindow.close();
	}

	// Pause on space key
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		if (!isPauseKeyPressed)
		{
			if (gameState == GameState::running) 
			{
				gameState = GameState::paused;
				txtState.setString("Paused");
				txtHelp.setString("Space to Play");
			}	
			else
			{
				gameState = GameState::running;
				txtState.setString("");
				txtHelp.setString("");
			}
				
		}
		isPauseKeyPressed = true;
	}
	else
	{
		isPauseKeyPressed = false;
	}

	// Reset on R key
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
	{
		reset();
	}
}

void BrickBreaker::HandleWindowEvents()
{
	sf::Event event;

	// Check for events
	while (gameWindow.pollEvent(event))
	{
		// Close window
		if (event.type == sf::Event::Closed)
		{
			gameWindow.close();
		}
	}
}
