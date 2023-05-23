#include "GameLoop.h"

int main()
{
	GameLoop* game = GameLoop::get();
	game->run();

	return 0;
}