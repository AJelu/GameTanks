#include "engine.h"

void Engine::EngineDraw(float& timer)
{
	Main_window.clear(Color::Black);
	Main_window.setView(CameraControl(Point_level.Draw(Main_window)));
	Main_window.display(); //end the current frame
}

View& Engine::CameraControl(View& player_camera)
{
    float temp_camera_x = player_camera.getCenter().x;
    float temp_camera_y = player_camera.getCenter().y;

    if (temp_camera_x < 515) temp_camera_x = 515; //left edge
    if (temp_camera_x > 7610) temp_camera_x = 7610; //right edge
    if (temp_camera_y < 385) temp_camera_y = 385; //upper edge
    if (temp_camera_y > 7750) temp_camera_y = 7750; //lower edge

    player_camera.setSize(SCREEN_RESOLUTION_X, SCREEN_RESOLUTION_Y);

    player_camera.setCenter(temp_camera_x, temp_camera_y);
    return player_camera;
}