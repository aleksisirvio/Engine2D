#include <raylib.h>

#include "GameLoop.h"
#include "Room.h"

GameLoop GameLoop::sInstance;

/********************************************************************
GameLoop::get

Returns the game loop singleton.
********************************************************************/
GameLoop* GameLoop::get()
{
	return &sInstance;
}

/********************************************************************
GameLoop::run

Run the game loop. Only call once at the beginning.
********************************************************************/
void GameLoop::run()
{
	if (mRunning)
		return;

	mRunning = true;

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
		switch (mState)
		{
		case (GameState::init):
			initGame();
			break;
		case (GameState::play):
			if (mPauseTimer > 0)
				mPauseTimer--;
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
	mState = GameState::pause;
}

/********************************************************************
GameLoop::pause

Pause game for as many frames as wanted.
********************************************************************/
void GameLoop::pause(char time)
{
	mPauseTimer = time;
}

/********************************************************************
GameLoop::unpause

Resume game.
********************************************************************/
void GameLoop::unpause()
{
	mState = GameState::play;
	mPauseTimer = 0;
}

/********************************************************************
GameLoop::initGame

Called once at the beginnign to do initializations.
********************************************************************/
void GameLoop::initGame()
{


	mState = GameState::play;
}

/********************************************************************
GameLoop::updateObjects

Invokes the update method of game objects in the update list.
********************************************************************/
void GameLoop::updateObjects()
{
	auto objs = InstLists::get(mUpdateKey);
	if (!objs)
		return;

	for (auto obj : *objs)
		obj->update();
}

/********************************************************************
GameLoop::drawObjects

Invokes the draw method of game objects in the draw list.
********************************************************************/
void GameLoop::drawObjects()
{
	auto objs = InstLists::get(mDrawKey);
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
	auto objs = InstLists::get(mDrawKey);
	if (!objs)
		return;

	objs->sort([](const GameObject* a, const GameObject* b)
	{
		return a->getDepth() < b->getDepth();
	});
}