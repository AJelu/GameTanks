#include "engine.h"

void Engine::EngineInpute() {
    if (im_server_) {
        //Point_level.InputKeyboard(bool, key);
        //Point_level.InputMouse(event_type, mouse_position);
        Point_level_->InputEnemy();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) Point_level_->InputKeyboard(0, sf::Keyboard::Up);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) Point_level_->InputKeyboard(0, sf::Keyboard::Left);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) Point_level_->InputKeyboard(0, sf::Keyboard::Right);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Point_level_->InputKeyboard(0, sf::Keyboard::Down);
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) Point_level_->InputKeyboard(0, sf::Keyboard::Space);
        
        sf::Event event;
        while (Main_window_.pollEvent(event)) {
            Point_level_->InputMouse(event.type, 
                sf::Vector2i(sf::Mouse::getPosition(Main_window_).x, 
                    sf::Mouse::getPosition(Main_window_).y));
            if (event.type == sf::Event::KeyReleased)
                Point_level_->InputKeyboard(0, event.key.code);
        }


    }
}