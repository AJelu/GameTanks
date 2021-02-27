#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Unit {
private:
	Texture unitTexture;  //object for texture
	Sprite unitSprite; //object for sprite's texture
	FloatRect unitRectangle; //object for storing sprite coordinates

	float speed_x_, speed_y_; //speed along the axes
	bool pressed_Up_, pressed_Left_, pressed_Right_, pressed_Down_; //movement positions

	float rotation_x;

	/* Game Input: */
	void ButtonsControl(); 

	/* Unit Functions: */
	void MoveUp();
	void MoveLeft();
	void MoveRight();
	void MoveDown();

	void StopUp();
	void StopLeft();
	void StopRight();
	void StopDown();

	void CreateMoveUnit();
	void ControlMoveUnit(float& game_time);

	/* Game Draw: */
	void UnitDraw(RenderWindow& main_Window);

public:
	Unit(FloatRect rectangle); /* rectangle takes coordinates X, Y, W, H 
	X & Y: respawn's coordinates on the map;   W & H: coordinates of physical boundaries */
	
	/* Game Update: */
	void UnitUpdateWithDrawWithInput(RenderWindow& main_Window, float& game_time);
};