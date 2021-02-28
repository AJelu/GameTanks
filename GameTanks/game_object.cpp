#include "objects.h"

GameObject::GameObject() : VisibleObject() {}

GameObject::GameObject(int id_object,
	sf::Vector2f coordinate_centre,
	sf::Vector2f offset_sprite_coordinate,
	string texture, int frame_size_x, int frame_size_y,
	int life_level) 
	: VisibleObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_size_x, frame_size_y)
{
	SetLifeLevel(life_level);
}

void GameObject::SetLifeLevel(int life_level)
{ life_level_ = life_level; }

int GameObject::GetLifeLevel() { return life_level_; }

void GameObject::AddCollision(RoundCollision* new_colision)
{
	// add to vector <RoundCollision*> collisions_;
}

float GameObject::DistanceToCollision(GameObject* game_object)
{
	// calculate all to all
	return 0;
}


GameObject::~GameObject() 
{
	//delete vector <RoundCollision*> collisions_;
}