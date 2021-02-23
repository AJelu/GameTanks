#pragma once
#include "Collisions.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

//this objects using in levels to create game experience: game menu, game levels

class BaseObject
{
protected:
	////BaseObjects * parent_ = nullptr;
	int x_, y_;

public:
	//send to object information or query and recv answer
	virtual int /*returm message*/ SendAndProcessingMessage(/*mess*/);
};

class VisibleObject : BaseObject
{
protected:
	bool need_redraw_image_; //using for redraw screen. if have changing - true
	bool visible_; //hidden or visible this object
	int height_, width_; //object params
	//texture; //object image

	//calculate if this object is within the range of the rectangle
	bool ObjectInRectangle(int x1, int y1, int x2, int y2, bool all_in_rect = false);
public:
	VisibleObject(int x, int y, int h, int w/*, texture*/);

	//get object parameters
	int GetCoordinateX();
	int GetCoordinateY();
	int GetHeight();
	int GetWidth();

	bool NeedRedrawImage(); //return true if need update image
	bool Visible();

	//set object parameters
	int SetCoordinate(int x_coordinate, int y_coordinate);
	int SetSize(int height, int width);
	int SetTexture(/*texture*/);

	bool Hide();
	bool Show();
	bool Draw(sf::RenderWindow* window, int offset_screen_x, int offset_screen_y);
};



class UiObject : VisibleObject
{
protected:
	bool focus_on_this_;
public:
	virtual int /*returm message*/ SendAndProcessingMessage(/*mess*/) override;
};

class Button : UiObject
{
protected:
	
public:
	virtual int /*returm message*/ SendAndProcessingMessage(/*mess*/) override;
};

//others ui objects, and camera



class GameObject : VisibleObject
{
private:
	int life;
	vector <RoundCollision>* collisions_;

public:
	float DistanceToCollision(GameObject* game_object);
};


class StaticObject : GameObject
{

};

//others statics objects. tree, stone, brick



class MovebleObject : GameObject
{
private:
	float vector_x, vector_y, speed;
	//game timer;
	////
};

//bang class

class TankObject : MovebleObject
{
	//+create bang
};