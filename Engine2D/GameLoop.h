#pragma once

enum class GameState
{
	init,
	play,
	pause
};

/********************************************************************
GameLoop

The heart of the engine. Starts the game, updates game objects,
draws game objects, and ends the game. Singleton implementation.
********************************************************************/
class GameLoop
{
public:
	static GameLoop* get();
	void run();
	void destroy();
	void pause();
	void pause(char time);
	void unpause();

private:
	GameLoop() = default;
	void initGame();
	void updateObjects();
	void drawObjects();
	void sortObjects();

	static GameLoop instance;

	GameState state = GameState::init;
	bool running = false;
	char pauseTimer = 0;

	int step_key{ -1 };
	int draw_key{ -1 };
};