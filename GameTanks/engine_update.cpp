#include "engine.h"

void Engine::EngineUpdate(float& game_time) {
	Point_level_->UpdateState(game_time);
	if (Status_server_ == StatusServer::SERVER) 
		Point_level_->CalculateCollisionOnLevel();
}