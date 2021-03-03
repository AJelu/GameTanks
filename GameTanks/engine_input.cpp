#include "engine.h"

void Engine::EngineInpute()
{
    if (im_server) {
        //Point_level.InputKeyboard(bool, key);
        //Point_level.InputMouse(event_type, mouse_position);
        Point_level.InputEnemy();

		if (Keyboard::isKeyPressed(Keyboard::Up)) Point_level.InputKeyboard(false, Keyboard::Up);
		if (Keyboard::isKeyPressed(Keyboard::Left)) Point_level.InputKeyboard(false, Keyboard::Left);
		if (Keyboard::isKeyPressed(Keyboard::Right)) Point_level.InputKeyboard(false, Keyboard::Right);
		if (Keyboard::isKeyPressed(Keyboard::Down)) Point_level.InputKeyboard(false, Keyboard::Down);
    }
}