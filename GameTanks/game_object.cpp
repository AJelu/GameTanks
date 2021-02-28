#include "objects.h"

GameObject::GameObject() : VisibleObject() 
{ SetLifeLevel(1); }

GameObject::GameObject(int id_object,
	sf::Vector2f coordinate_centre,
	sf::Vector2f offset_sprite_coordinate,
	string texture, int frame_count_x, int frame_count_y,
	int life_level) 
	: VisibleObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y)
{
	SetLifeLevel(life_level);
}

void GameObject::SetLifeLevel(int life_level)
{ life_level_ = life_level; }

int GameObject::GetLifeLevel() 
{ return life_level_; }

void GameObject::AddCollision(RoundCollision* new_colision)
{ collisions_.push_back(new_colision); }

float GameObject::DistanceToCollision(GameObject* game_object)
{
	// calculate all to all <---------------------------------------
	return 0;
}


GameObject::~GameObject() 
{
	for (int i = 0; i < collisions_.size(); i++) {
		delete collisions_[i];
	}
}