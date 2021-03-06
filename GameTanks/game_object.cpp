#include "objects.h"
#include <cmath>

GameObject::GameObject() : VisibleObject()
{
	this->SetLifeLevel(1);
	CollisionOn();
	max_collision_distance = 0;
}

GameObject::GameObject(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	string const& texture, int const& frame_count_x, int const& frame_count_y,
	int const& life_level)
	: VisibleObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y)
{
	this->SetLifeLevel(life_level);
	CollisionOn();
	max_collision_distance = 0;
}

void GameObject::SetLifeLevel(int const& life_level)
{
	if (life_level_ != 0 && life_level == 0) { PlayAnimateDie(); }
	life_level_ = life_level;
	if (life_level_ < 0) { life_level_ = 0; }
}

int GameObject::GetLifeLevel() 
{ return life_level_; }

void GameObject::PlayAnimateDie() {}

void GameObject::AddCollision(RoundCollision* new_colision)
{
	if (new_colision != nullptr) {
		collisions_.push_back(new_colision);
		new_colision->GetCoordinate().x;
		float temp = powf(new_colision->GetCoordinate().x, 2) +
			powf(new_colision->GetCoordinate().x, 2);
		if (temp > 0) {
			temp = sqrtf(temp);
		}
			temp += new_colision->GetRadius();
		if (temp > max_collision_distance) {
			max_collision_distance = temp;
		}
	}
}

float GameObject::SafeDistanceToCollision(GameObject* game_object)
{
	if (collision_off) return 0;
	return this->GetDistanceToPoint(game_object->GetCoordinateCentre()) -
		this->max_collision_distance - game_object->max_collision_distance - 1;
}

bool GameObject::Collision(GameObject* Game_object, bool healt) //not have collision - return true
{
	if (collision_off) return true;
	Vector2f point_1, point_2;
	float distance;
	if (Game_object != nullptr) {
		for (int i = 0; i < this->collisions_.size(); i++) {
			point_1 = this->ChangeVectorByDirection(
				this->collisions_[i]->GetCoordinate());
			point_1.x += this->GetCoordinateCentre().x;
			point_1.y *= -1;
			point_1.y += this->GetCoordinateCentre().y;
			for (int j = 0; j < Game_object->collisions_.size(); j++) {
				point_2 = Game_object->ChangeVectorByDirection(
					Game_object->collisions_[j]->GetCoordinate());
				point_2.x += Game_object->GetCoordinateCentre().x;
				point_2.y *= -1;
				point_2.y += Game_object->GetCoordinateCentre().y;
				
				distance = sqrtf(powf(point_1.x - point_2.x, 2) +
					powf(point_1.y - point_2.y, 2));
				if ((distance - this->collisions_[i]->GetRadius() -
					Game_object->collisions_[j]->GetRadius()) < 0) {
					if (healt) {
						this->RestorePreviousState();
						Game_object->RestorePreviousState();
					}
					return false;
				}
			}
			if (point_1.x - this->collisions_[i]->GetRadius() < 0 ||
				point_1.y - this->collisions_[i]->GetRadius() < 0) {
				return false;
			}
		}
	}
	return true;
}

void GameObject::CollisionOff()
{ collision_off = true; }

void GameObject::CollisionOn()
{ collision_off = false; }

GameObject::~GameObject()
{
	for (int i = 0; i < collisions_.size(); i++) {
		if (collisions_.at(i)) delete collisions_[i];
	}
}