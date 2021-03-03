#include "engine.h"

void Engine::EngineDraw(float& timer)
{
	Main_window.clear(Color::Black);
	Point_level.Draw(Main_window);

	//TestUnit.UnitUpdateWithDrawWithInput(Main_window, timer); /*test*/

	Main_window.display(); //end the current frame
}