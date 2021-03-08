#include "objects.h"
#include <cmath>

GameObject::GameObject() : VisibleObject() {
	this->SetLifeLevel(1);
	CollisionOn();
	max_collision_distance_ = 0;
}

GameObject::GameObject(int const& id_object,
			sf::Vector2f const& coordinate_centre,
			sf::Vector2f const& offset_sprite_coordinate,
			std::string const& texture, int const& frame_count_x, int const& frame_count_y,
			int const& life_level)
			: VisibleObject(id_object, coordinate_centre, offset_sprite_coordinate,
				texture, frame_count_x, frame_count_y) {
	this->SetLifeLevel(life_level);
	CollisionOn();
	max_collision_distance_ = 0;
}

void GameObject::SetLifeLevel(int const& life_level) {
	if (life_level_ != life_level && life_level_ >= 0) {
		if (life_level == 0) { PlayAnimateDie(); }
		if (life_level_ == 0) { PlayAnimateLife(); }

		life_level_ = life_level;
	}
}

int GameObject::GetLifeLevel() { return life_level_; }

void GameObject::PlayAnimateDie() { }

void GameObject::PlayAnimateLife() { }

void GameObject::AddCollision(RoundCollision* new_colision) {
	if (new_colision != nullptr) {
		Collisions_.push_back(new_colision);
		float temp = powf(new_colision->GetCoordinate().x, 2) +
					 powf(new_colision->GetCoordinate().y, 2);
		if (temp > 0) temp = sqrtf(temp);
		temp += new_colision->GetRadius();
		if (temp > max_collision_distance_) max_collision_distance_ = temp;
	}
}

float GameObject::SafeDistanceToCollision(GameObject* game_object, 
				int level_size_x, int level_size_y, int level_size_border) {
	if (collision_off_) return 0;
	
	float result = 1, temp;
	result = this->GetCoordinateCentre().x - max_collision_distance_ - level_size_border;
	temp = this->GetCoordinateCentre().y - max_collision_distance_ - level_size_border;
	if (temp < result) result = temp;
	temp = level_size_x - (this->GetCoordinateCentre().x + max_collision_distance_ + level_size_border);
	if (temp < result) result = temp;
	temp = level_size_y - (this->GetCoordinateCentre().y + max_collision_distance_ + level_size_border);
	if (temp < result) result = temp;
	temp = this->GetDistanceToPoint(game_object->GetCoordinateCentre()) -
		this->max_collision_distance_ - game_object->max_collision_distance_;
	if (temp < result) result = temp;

	return result - 1;
}

//not have collision - return true
bool GameObject::Collision(GameObject* Game_object, 
				int level_size_x, int level_size_y, int level_size_border,
				bool healt) {
	if (collision_off_) return true;
	Vector2f point_1, point_2;
	float distance;
	if (Game_object != nullptr) {
		for (int i = 0; i < (int)this->Collisions_.size(); i++) {
			point_1 = this->ChangeVectorByDirection(
				this->Collisions_[i]->GetCoordinate());
			point_1.x += this->GetCoordinateCentre().x;
			point_1.y *= -1;
			point_1.y += this->GetCoordinateCentre().y;
			for (int j = 0; j < (int)Game_object->Collisions_.size(); j++) {
				point_2 = Game_object->ChangeVectorByDirection(
					Game_object->Collisions_[j]->GetCoordinate());
				point_2.x += Game_object->GetCoordinateCentre().x;
				point_2.y *= -1;
				point_2.y += Game_object->GetCoordinateCentre().y;
				
				distance = sqrtf(powf(point_1.x - point_2.x, 2) +
					powf(point_1.y - point_2.y, 2));
				if ((distance - this->Collisions_[i]->GetRadius() -
					Game_object->Collisions_[j]->GetRadius()) < 0) {
					if (healt) {
						this->RestorePreviousState();
						Game_object->RestorePreviousState();
					}
					return false;
				}
			}
			if (healt && 
				(point_1.x - this->Collisions_[i]->GetRadius() < level_size_border ||
				point_1.y - this->Collisions_[i]->GetRadius() < level_size_border ||
				point_1.x + this->Collisions_[i]->GetRadius() > level_size_x - level_size_border ||
				point_1.y + this->Collisions_[i]->GetRadius() > level_size_y - level_size_border)) {
				this->RestorePreviousState();
				return false;
			}
		}
	}
	return true;
}

void GameObject::CollisionOff() { collision_off_ = true; }

void GameObject::CollisionOn() { collision_off_ = false; }

GameObject::~GameObject() {
	for (int i = 0; i < (int)Collisions_.size(); i++) {
		if (Collisions_.at(i)) delete Collisions_[i];
	}
}