#pragma once
#include "Collisions.h"
#include <string>

/* Jelu. line 69: int SendAndProcessingMessage(int mess)+ override; */

using namespace std;

//this objects using in levels to create game expiriens: game menu, game levels

class BaseObjects 
{
protected:
	//BaseObjects * parent_ = nullptr;
	int x_, y_;
	bool level_position; //use level coordinate or screen coordinate

public:
	virtual string GetClassName();
	virtual int /*returm message*/ SendAndProcessingMessage(/*mess*/);
	virtual void /*returm message*/ GetMassages();

	bool Get;
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
	bool Draw(/*canvas,*/ int offset_level_x, int offset_level_y);
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
	int SendAndProcessingMessage(int mess) override; /* +"override" for accurate virtualization */
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