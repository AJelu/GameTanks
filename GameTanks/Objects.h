#pragma once
#include "Collisions.h"
//this objects using in levels to create game expiriens: game menu, game levels

class BaseObjects 
{
	//daughter objects?
};

class VisibleObject : BaseObjects
{
	//size, coordinate, picture, function draw...
};



class UiObject : VisibleObject
{
	
};

class Button : UiObject
{

};

//others ui objects, and camera



class GameObject : BaseObjects
{
	//colisions
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