#include "ready_objects.h"

MovebleObject* RedTank::Shot()
{
	//create chot
	return new RedTank(1, this->GetCoordinateCentre().x, this->GetCoordinateCentre().y);
}

RedTank::RedTank(int const& id_object, float const& spawn_x, float const& spawn_y):TankObject(id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 157), //offset
		"Data/Tank4.png", //texture
		5, 2,	//frame count
		1,		//life level
		200,	//speed move
		0,		//freeze time
		100,	//rotation speed
		100,	//speed shot
		400,	//shot distance
		1500)	//time freeze shot (to next shot)
{
	this->AddCollision(new RoundCollision(Vector2f(0, 0), 50));
}

void RedTank::PlayAnimateDie()
{
}

void RedTank::PlayAnimateMovePlus()
{
	this->StartPlayAnimation(1, 1, 5, 50);
}

void RedTank::PlayAnimateMoveMinus()
{
	this->StartPlayAnimation(1, 5, 1, 150);
}

void RedTank::PlayAnimateRotateÑlockwise()
{
	this->StartPlayAnimation(2, 1, 5, 70);
}

void RedTank::PlayAnimateRotateÑounterclockwise()
{
	this->StartPlayAnimation(2, 5, 1, 70);
}
