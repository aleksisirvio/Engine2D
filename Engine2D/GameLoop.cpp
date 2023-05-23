#include <raylib.h>

#include "GameLoop.h"
#include "InstLists.h"

GameLoop GameLoop::instance;

/********************************************************************
GameLoop::get

Returns the game loop singleton.
********************************************************************/
GameLoop* GameLoop::get()
{
	return &instance;
}

/********************************************************************
GameLoop::run

Run the game loop. Only call once at the beginning.
********************************************************************/
void GameLoop::run()
{
	if (running)
		return;

	running = true;

	Rectangle r = { 0.0f, 0.0f, 1920, -1080 };
	Vector2 v = { 0, 0 };

	InitWindow(1920, 1080, "Title");

	DisableCursor();

	RenderTexture2D surface = LoadRenderTexture(1920, 1080);

	Camera2D camera{};

	SetTargetFPS(60);

	// Enter game loop
	while (!WindowShouldClose())
	{
		// Update game objects
		switch (state)
		{
		case (GameState::init):
			initGame();
			break;
		case (GameState::play):
			if (pauseTimer > 0)
				pauseTimer--;
			else
			{
				sortObjects();
				updateObjects();
			}
			break;
		case (GameState::pause):
			break;
		}

		// Start drawing
		BeginDrawing();
		ClearBackground(LIGHTGRAY);

		// Draw game onto a texture
		BeginTextureMode(surface);
		BeginMode2D(camera);
		ClearBackground(LIGHTGRAY);
		drawObjects();
		EndMode2D();
		EndTextureMode();

		// Draw game scaled to size of the game window
		DrawTexturePro(surface.texture, r, {0, 0, 1920, 1080}, v, 0, WHITE);

		// End drawing
		EndDrawing();
	}
}

/********************************************************************
GameLoop::pause

Pause game indefinitely.
********************************************************************/
void GameLoop::pause()
{
	state = GameState::pause;
}

/********************************************************************
GameLoop::pause

Pause game for as many frames as wanted.
********************************************************************/
void GameLoop::pause(char time)
{
	pauseTimer = time;
}

/********************************************************************
GameLoop::unpause

Resume game.
********************************************************************/
void GameLoop::unpause()
{
	state = GameState::play;
	pauseTimer = 0;
}

/********************************************************************
GameLoop::initGame

Called once at the beginnign to do initializations.
********************************************************************/
void GameLoop::initGame()
{


	state = GameState::play;
}

/********************************************************************
GameLoop::updateObjects

Invokes the step method of game objects in the step list.
********************************************************************/
void GameLoop::updateObjects()
{
	auto objs = InstLists::get(step_key);
	if (!objs)
		return;

	for (auto obj : *objs)
		obj->step();
}

/********************************************************************
GameLoop::drawObjects

Invokes the draw method of game objects in the draw list.
********************************************************************/
void GameLoop::drawObjects()
{
	auto objs = InstLists::get(draw_key);
	if (!objs)
		return;

	for (auto obj : *objs)
		obj->draw();
}

/********************************************************************
GameLoop::sortObjects

Sorts game objects in the draw list according to their depth.
********************************************************************/
void GameLoop::sortObjects()
{
	auto objs = InstLists::get(draw_key);
	if (!objs)
		return

	objs->sort([](GameObject* a, GameObject* b)
	{
		return a->getDepth() < b->getDepth();
	});
}