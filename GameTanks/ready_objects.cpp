#include "ready_objects.h"

void Bullet::PlayAnimateDie() { this->StartPlayAnimation(1, 1, 8, 40); }

void Bullet::PlayAnimateLife() { this->StartPlayAnimation(2, 1, 4, 50); }

void Bullet::PlayAnimateMovePlus() { this->StartPlayAnimation(2, 1, 8, 20); }

Bullet::Bullet(int const& id_object, GameObject* Parrent) : MovebleObject(
	id_object,
	sf::Vector2f(0, 0), //coordinate centr
	sf::Vector2f(96, 96), //offset
	"Data/Animation/Boom_3.png", //texture
	8, 2,	//frame count
	1000000,//max life level
	500,	//speed move
	0,		//freeze time
	100,	//rotation speed
	Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
}


TypedTank::TypedTank(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	std::string const& texture,
	int const& max_life_level,
	float const& speed, float const& freeze_time,
	float const& rotation_speed, sf::Vector2f const& point_create_shot_by_vector,
	int const& shot_life, float const& speed_shot, float const& shot_distance,
	float const& time_freeze_shot,
	GameObject* Parrent) : TankObject(id_object, coordinate_centre,
		offset_sprite_coordinate, texture,
		12, 4, max_life_level,
		speed, freeze_time, rotation_speed, point_create_shot_by_vector,
		shot_life, speed_shot, shot_distance, time_freeze_shot, Parrent){ }

void TypedTank::PlayAnimateDie() { this->StartPlayAnimation(2, 1, 12, 70); }

void TypedTank::PlayAnimateLife() { this->StartPlayAnimation(1, 12, 1, 70); }

void TypedTank::PlayAnimateMovePlus() { this->StartPlayAnimation(3, 1, 12, 40); }

void TypedTank::PlayAnimateMoveMinus() { this->StartPlayAnimation(3, 12, 1, 40); }

void TypedTank::PlayAnimateRotateÑlockwise() { this->StartPlayAnimation(4, 1, 12, 100); }

void TypedTank::PlayAnimateRotateÑounterclockwise() { this->StartPlayAnimation(4, 12, 1, 100); }


RedTank::RedTank(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 158), //offset
		"Data/Unit/Tank1.png", //texture
		10,		//max life level
		200,	//speed move
		0,		//freeze time
		100,	//rotation speed
		sf::Vector2f(-1,150),	//create point shot
		1,		//shot life
		300,	//speed shot
		400,	//shot distance
		500,	//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
	/*this->AddCollision(new RoundCollision(sf::Vector2f(30, 30), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(-30, 30), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(-30, -40), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(30, -40), 20));

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 60), 10));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 60), 10));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 80), 10));*/
}

MovebleObject* RedTank::Shot() { return new Bullet(1, this); }


Tank2::Tank2(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 137), //offset
		"Data/Unit/Tank2.png", //texture
		5,		//max life level
		200,	//speed move
		0,		//freeze time
		100,	//rotation speed
		sf::Vector2f(-6, 129),	//create point shot
		1,		//shot life
		300,	//speed shot
		400,	//shot distance
		500,	//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
	/*this->AddCollision(new RoundCollision(sf::Vector2f(30, 30), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(-30, 30), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(-30, -40), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(30, -40), 20));

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 60), 10));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 60), 10));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 80), 10));*/
}

MovebleObject* Tank2::Shot() { return new Bullet(1, this); }


Tank3::Tank3(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 84), //offset
		"Data/Unit/Tank3.png", //texture
		5,		//max life level
		200,	//speed move
		0,		//freeze time
		100,	//rotation speed
		sf::Vector2f(0, 77),	//create point shot
		1,		//shot life
		300,	//speed shot
		400,	//shot distance
		500,	//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
	/*this->AddCollision(new RoundCollision(sf::Vector2f(30, 30), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(-30, 30), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(-30, -40), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(30, -40), 20));

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 60), 10));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 60), 10));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 80), 10));*/
}

MovebleObject* Tank3::Shot() { return new Bullet(1, this); }


Tank4::Tank4(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 76), //offset
		"Data/Unit/Tank4.png", //texture
		5,		//max life level
		300,	//speed move
		0,		//freeze time
		200,	//rotation speed
		sf::Vector2f(0, 68),	//create point shot
		1,		//shot life
		500,	//speed shot
		100,	//shot distance
		100,	//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
	/*this->AddCollision(new RoundCollision(sf::Vector2f(30, 30), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(-30, 30), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(-30, -40), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(30, -40), 20));

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 60), 10));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 60), 10));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 80), 10));*/
}

MovebleObject* Tank4::Shot() { return new Bullet(1, this); }


Tank5::Tank5(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 130), //offset
		"Data/Unit/Tank5.png", //texture
		5,		//max life level
		200,	//speed move
		0,		//freeze time
		100,	//rotation speed
		sf::Vector2f(0, 121),	//create point shot
		1,		//shot life
		300,	//speed shot
		400,	//shot distance
		500,	//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
	/*this->AddCollision(new RoundCollision(sf::Vector2f(30, 30), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(-30, 30), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(-30, -40), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(30, -40), 20));

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 60), 10));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 60), 10));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 80), 10));*/
}

MovebleObject* Tank5::Shot() { return new Bullet(1, this); }


Tank6::Tank6(int const& id_object, float const& spawn_x, float const& spawn_y,
	GameObject* Parrent) : TypedTank(
		id_object,
		sf::Vector2f(spawn_x, spawn_y), //coordinate centr
		sf::Vector2f(60, 88), //offset
		"Data/Unit/Tank6.png", //texture
		5,		//max life level
		100,	//speed move
		0,		//freeze time
		50,	//rotation speed
		sf::Vector2f(0, 80),	//create point shot
		10,		//shot life
		100,	//speed shot
		600,	//shot distance
		2000,	//time freeze shot (to next shot)
		Parrent) {
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 50));
	/*this->AddCollision(new RoundCollision(sf::Vector2f(30, 30), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(-30, 30), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(-30, -40), 20));
	this->AddCollision(new RoundCollision(sf::Vector2f(30, -40), 20));

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 60), 10));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 60), 10));
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 80), 10));*/
}

MovebleObject* Tank6::Shot() { return new Bullet(1, this); }