#include "engine.h"

void Engine::EngineInpute() {
    if (im_server_) {
        //Point_level.InputKeyboard(bool, key);
        //Point_level.InputMouse(event_type, mouse_position);
        Point_level_->InputEnemy();

		if (Keyboard::isKeyPressed(Keyboard::Up)) Point_level_->InputKeyboard(0, Keyboard::Up);
		if (Keyboard::isKeyPressed(Keyboard::Left)) Point_level_->InputKeyboard(0, Keyboard::Left);
		if (Keyboard::isKeyPressed(Keyboard::Right)) Point_level_->InputKeyboard(0, Keyboard::Right);
        if (Keyboard::isKeyPressed(Keyboard::Down)) Point_level_->InputKeyboard(0, Keyboard::Down);
        if (Keyboard::isKeyPressed(Keyboard::Space)) Point_level_->InputKeyboard(0, Keyboard::Space);


        if (Keyboard::isKeyPressed(Keyboard::W)) Point_level_->InputKeyboard(1, Keyboard::Up);
        if (Keyboard::isKeyPressed(Keyboard::A)) Point_level_->InputKeyboard(1, Keyboard::Left);
        if (Keyboard::isKeyPressed(Keyboard::D)) Point_level_->InputKeyboard(1, Keyboard::Right);
        if (Keyboard::isKeyPressed(Keyboard::S)) Point_level_->InputKeyboard(1, Keyboard::Down);
        if (Keyboard::isKeyPressed(Keyboard::F)) Point_level_->InputKeyboard(1, Keyboard::Space);
    }
}