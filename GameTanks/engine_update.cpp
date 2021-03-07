#include "engine.h"

void Engine::EngineUpdate(float& game_time)
{
	if (im_server) Point_level->UpdateState(game_time);
}