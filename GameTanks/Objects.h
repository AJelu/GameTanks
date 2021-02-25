#pragma once
#include "Collisions.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

//this objects using in levels to create game experience: game menu, game levels

class BaseObject
{
private:
	int x_coordinate_, y_coordinate_;
	int id_object; //for synchronize by lan

public:
	BaseObject(int id_object, int x, int y);	

	//get object parameters
	int GetCoordinateX();
	int GetCoordinateY();
	int GetIdObject();
	//set object parameters
	virtual int SetCoordinate(int x_coordinate, int y_coordinate);
	
	~BaseObject();
};

class VisibleObject : BaseObject
{
private:
	bool need_redraw_image_; //using for redraw screen. if have changing - true
	bool visible_; //hidden or visible this object
	////int height_, width_; //object params <-----------------------
	
	//textures; //object image, animate <-----------------------
protected:
	//calculate if this object is within the range of the rectangle
	bool ObjectInRectangle(int x1, int y1, int x2, int y2, bool all_in_rect = false);
	void SetNeedRedrawImage();
public:
	VisibleObject(int id_object, 
		int x, int y/*, int h, int w, textures*/);

	//get object parameters
	int GetHeight();
	int GetWidth();

	bool NeedRedrawImage(); //return true if need update image
	bool Visible();

	//set object parameters
	int SetCoordinate(int x_coordinate, int y_coordinate) override;
	int SetSize(int height, int width); //?????????????????? <-----------------------
	int SetTexture(/*texture*/);

	bool Hide();
	bool Show();
	bool Draw(sf::RenderWindow* window, int offset_screen_x, int offset_screen_y/*, timer <-----------------------*/);
	~VisibleObject();
};



class UiObject : VisibleObject
{
private:
	bool focus_on_this_, down_on_this_, up_on_this_;
	string text_;
public:
	bool IsFocusOnThis(int x, int y);
	bool IsDownOnThis(int x, int y);
	bool IsUpOnThis(int x, int y);
	void AddInputText(string text);
	void SetText(string text);

	bool FocusOnThis();
	bool DownOnThis();
	bool UpOnThis();
	string GetText();

	bool Draw(sf::RenderWindow* window);
	~UiObject();
};

class Button : UiObject
{
public:
	Button(int id_object, 
		int x, int y/*, int h, int w, textures*/, 
		string text);
	~Button();
};

//others ui objects



class GameObject : VisibleObject
{
private:
	int life_level_;
	vector <RoundCollision>* collisions_;

public:
	GameObject(int id_object, 
		int x, int y/*, int h, int w, textures*/, 
		int life_level);

	void SetLifeLevel();
	int GetLifeLevel();
	void AddCollision(RoundCollision* new_colision);
	float DistanceToCollision(GameObject* game_object);
	~GameObject();
};

/*
class StaticObject : GameObject
{

};

//others statics objects. tree, stone, brick
*/


class MovebleObject : GameObject
{
private:
	float vector_x_, vector_y_, speed_, distance_;

	void RecalculateVector();

public:
	MovebleObject(int id_object, 
		int x, int y/*, int h, int w, textures*/, 
		int life_level, float speed);

	//set object parameters
	void SetVector(float vector_x, float vector_y);
	void SetSpeed(float speed);
	void SetDistance(float distance, bool add_to_previous = false);

	//get object parameters
	float GetVectorX();
	float GetVectorY();
	float GetSpeed();
	float GetDistance();

	void MoveTo(int move_to_x, int move_to_y);

	//for recalculate position ((vector+speed+distance)*timer)
	void RecalculateState(/*timer*/);

	//for heal collisions
	void TerminateCollision(GameObject game_object);
	void TerminateCollision(MovebleObject moveble_object);
	~MovebleObject();
};

class TankObject : MovebleObject
{
private:
	float speed_shot_, max_shot_distance;
public:
	TankObject(int id_object, 
		int x, int y/*, int h, int w, textures*/,
		int life_level, float speed, float speed_shot_, float max_shot_distance);
	MovebleObject CreateShot();
	~TankObject();
};