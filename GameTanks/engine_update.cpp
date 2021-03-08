#include "engine.h"

void Engine::EngineUpdate(float& game_time) {
	if (im_server_) Point_level_->UpdateState(game_time);
}