#include "objects.h"

GameObject::GameObject() : VisibleObject() 
{ this->SetLifeLevel(1); }

GameObject::GameObject(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	string const& texture, int const& frame_count_x, int const& frame_count_y,
	int const& life_level)
	: VisibleObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y)
{
	this->SetLifeLevel(life_level);
}

void GameObject::SetLifeLevel(int const& life_level)
{ life_level_ = life_level; }

int GameObject::GetLifeLevel() 
{ return life_level_; }

void GameObject::AddCollision(RoundCollision* const& new_colision)
{ collisions_.push_back(new_colision); }

float GameObject::DistanceToCollision(GameObject* const& game_object)
{
	// calculate all to all <---------------------------------------
	return 0;
}


GameObject::~GameObject() 
{
	for (int i = 0; i < collisions_.size(); i++) {
		if (collisions_.at(i)) delete collisions_[i];
	}
}