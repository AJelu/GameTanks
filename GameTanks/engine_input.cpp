#include "engine.h"

void Engine::EngineInpute()
{
    if (im_server) {
        //Point_level->InputKeyboard(bool, key);
        //Point_level->InputMouse(event_type, mouse_position);
        Point_level->InputEnemy();
    }
}