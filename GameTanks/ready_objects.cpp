#include "ready_objects.h"

RedTank::RedTank(int const& id_object, float const& spawn_x, float const& spawn_y, GameObject* Parrent)
	:TankObject(id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 157), //offset
		"Data/Tank4.png", //texture
		5, 2,	//frame count
		5,		//life level
		200,	//speed move
		0,		//freeze time
		100,	//rotation speed
		300,	//speed shot
		400,	//shot distance
		500,	//time freeze shot (to next shot)
		Parrent) {	
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
}

MovebleObject* RedTank::Shot() {
	//create chot
	RedTank* t = new RedTank(1, this->GetCoordinateCentre().x, this->GetCoordinateCentre().y, this);
	t->SetLifeLevel(1);
	return t;
}

void RedTank::PlayAnimateDie() {
	this->StartPlayAnimation(2, 1, 5, 500);
}

void RedTank::PlayAnimateLife() {
	this->StartPlayAnimation(1, 1, 5, 500);
}

void RedTank::PlayAnimateMovePlus() {
	this->StartPlayAnimation(1, 1, 5, 50);
}

void RedTank::PlayAnimateMoveMinus() {
	this->StartPlayAnimation(1, 5, 1, 150);
}

void RedTank::PlayAnimateRotateÑlockwise() {
	this->StartPlayAnimation(2, 1, 5, 70);
}

void RedTank::PlayAnimateRotateÑounterclockwise() {
	this->StartPlayAnimation(2, 5, 1, 70);
}

void RedTank::RestoreLife() { this->SetLifeLevel(5); }
