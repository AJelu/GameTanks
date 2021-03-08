#include "engine.h"

void Engine::EngineDraw(float& timer)  {
	Main_window_.clear(Color::Black);
	Main_window_.setView(Point_level_->Draw(Main_window_));
	Main_window_.display(); //end the current frame
}