#include "engine.h"

void Engine::EngineDraw()  {
	Main_window_.clear(sf::Color::Black);
	Main_window_.setView(Point_level_->Draw(Main_window_));
	Main_window_.display();
}