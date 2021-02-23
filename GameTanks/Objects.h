#pragma once
#include "Collisions.h"
#include <string>

using namespace std;

//this objects using in levels to create game expiriens: game menu, game levels

class BaseObjects 
{
protected:
	//BaseObjects * parent_ = nullptr;
	int x_, y_;
	bool start_point_level_; //use level start point or screen start point

public:
	//using for identity daughter classes
	virtual string GetClassName();
	//send to object information or query and recv answer
	virtual int /*returm message*/ SendAndProcessingMessage(/*mess*/);
	virtual void /*returm message*/ GetMassages();

	bool StartPointLevel();
	void SetStartPointLevel();
};

class VisibleObject : BaseObjects
{
protected:
	bool need_redraw_image_;
	bool visible_;
	int layer_;
	int height_, width_;
	//texture;
public:
	VisibleObject(int x, int y, int h, int w, /*texture,*/ int layer);

	int GetLayer();
	int GetCoordinateX();
	int GetCoordinateY();
	int GetHeight();
	int GetWidth();
	bool NeedRedrawImage();
	bool Visible();

	int SetLayer(int layer);
	int SetCoordinate(int x_coordinate, int y_coordinate);
	int SetSize(int height, int width);
	int SetTexture(/*texture*/);

	bool Hide();
	bool Show();
	bool Draw(/*canvas,*/ int offset_screen_x, int offset_screen_y);
};



class UiObject : VisibleObject
{
protected:
	bool focus_on_this_;
public:
	virtual int SendAndProcessingMessage(int mess);
};

class Button : UiObject
{
protected:
	
public:
	int SendAndProcessingMessage(int mess);
};

//others ui objects, and camera



class GameObject : BaseObjects
{
	//add colisions
};


class StaticObject : GameObject
{

};

//others statics objects. tree, stone, brick



class MovebleObject : GameObject
{

};

class TankObject : MovebleObject
{

};