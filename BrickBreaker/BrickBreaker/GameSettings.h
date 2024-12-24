#pragma once


// Globals
struct WindowProperties
{
	static constexpr int Hieght{ 450 };
	static constexpr int Width{ 520 };
	static constexpr int FrameRate{ 60 };
};

struct GameProperties
{
	static constexpr int PlayerLives{ 3 };
	static constexpr float BallSize{ 10.0f };
	static constexpr float BallSpeed{ 3.0f };

	static constexpr float PaddleWidth{ 100.0f };
	static constexpr float PaddleHeight{ 5.0f };
	static constexpr float PaddleSpeed{ 5.0f };

	static constexpr float BrickWidth{ 50.0f };
	static constexpr float BrickHeight{ 15.0f };
	static constexpr float BrickStartOffset{ 0.0f };
	static constexpr int BrickRows{ 1 };
	static constexpr int BrickCols{ 1 };
	static constexpr int BrickStrength{5};

};

enum class GameState { running, paused, gameOver ,gameWon };
