#include "TestUnitController.h"

Unit::Unit(FloatRect rectangle)
{
	unitTexture.loadFromFile("Data/Tank2.png"); 
	unitSprite.setTexture(unitTexture);

	speed_x_, speed_y_ = 0;

	rotation_x = 0;

	pressed_Up_ = false;
	pressed_Left_ = false;
	pressed_Right_ = false;
	pressed_Down_ = false;
	
	unitRectangle = rectangle;
	/*	unitRectangle has variables:
			unitRect.left = X;		unitRect.width = W;
			unitRect.top = Y;		unitRect.height = H;
	*/

	//unitSprite.setTextureRect(IntRect(0, 0, 124, 233));
	/* setTextureRect(IntRect(X1, Y1, X2, Y2):
		 X1: sprite point in the picture by X;		Y1: sprite image size by X;
		 X2: sprite point in the picture by Y;		Y2: sprite image size by Y;
	*/
	unitSprite.setTextureRect(IntRect(0, 0, 124, 233));
}

/* Game Input: */
void Unit::ButtonsControl()
{
	if (Keyboard::isKeyPressed(Keyboard::Up)) MoveUp();
	else StopUp();
	if (Keyboard::isKeyPressed(Keyboard::Left)) MoveLeft();
	else StopLeft();
	if (Keyboard::isKeyPressed(Keyboard::Right)) MoveRight();
	else StopRight();
	if (Keyboard::isKeyPressed(Keyboard::Down)) MoveDown();
	else StopDown();
}

/* Unit Functions: */
void Unit::MoveUp() { pressed_Up_ = true; }

void Unit::MoveLeft() { pressed_Left_ = true; }

void Unit::MoveRight() { pressed_Right_ = true; }

void Unit::MoveDown() { pressed_Down_ = true; }

void Unit::StopUp() { pressed_Up_ = false; }

void Unit::StopLeft() { pressed_Left_ = false; }

void Unit::StopRight() { pressed_Right_ = false; }

void Unit::StopDown() { pressed_Down_ = false; }

void Unit::CreateMoveUnit()
{
	if (pressed_Up_) {
		speed_y_ = -0.1f;
		//unitSprite.move(0, -1);
		//change direction of the sprite picture to UP
		//unitSprite.setTextureRect(IntRect(0, 0, 124, 233)); 
	}
	if (pressed_Left_) {
		//speed_x_ = -0.1f;
		unitSprite.rotate(rotation_x += 1);
		//change direction of the sprite picture to LEFT
		//unitSprite.setTextureRect(IntRect(476, 112, 224, 114)); 
	}
	if (pressed_Right_) {
		
		//speed_x_ = 0.1f;
		unitSprite.rotate(rotation_x -= 1);
		//change direction of the sprite picture to RIGTH
		//unitSprite.setTextureRect(IntRect(250, 112, 224, 114)); 
	}
	if (pressed_Down_) {
		speed_y_ = 0.1f;
		//unitSprite.move(0, 1);
		//change direction of the sprite picture to DOWN
		//unitSprite.setTextureRect(IntRect(125, 0, 124, 233));
	}
	unitSprite.setOrigin(unitSprite.getTextureRect().width / 2, unitSprite.getTextureRect().height / 2);
	unitSprite.setRotation(rotation_x);
	//unitSprite.setPosition(unitRectangle.left / 2, unitRectangle.top / 2);
}

void Unit::ControlMoveUnit(float& game_time)
{
	//change position taking into speed and playing time
	unitRectangle.left += speed_x_ * game_time; 
	unitRectangle.top += speed_y_ * game_time;
	//unitSprite.setPosition(unitRectangle.left, unitRectangle.top); //fixed position unit
	speed_x_ = 0;
	speed_y_ = 0;
}

/* Game Update: */
void Unit::UnitUpdateWithDrawWithInput(RenderWindow& main_Window, float& game_time)
{
	ButtonsControl();
	ControlMoveUnit(game_time);
	CreateMoveUnit();
	UnitDraw(main_Window);
}

/* Game Draw: */
void Unit::UnitDraw(RenderWindow& main_Window) { main_Window.draw(unitSprite); }

