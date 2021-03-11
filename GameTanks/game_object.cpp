#include "objects.h"
#include <cmath>

GameObject::GameObject() : VisibleObject() {
	this->SetLifeLevel(1);
	this->CollisionOn();
	max_collision_distance_ = 0;
	Parrent_ = nullptr;
}

GameObject::GameObject(int const& id_object,
			sf::Vector2f const& coordinate_centre,
			sf::Vector2f const& offset_sprite_coordinate,
			std::string const& texture, 
			int const& frame_count_x, int const& frame_count_y,
			int const& life_level, GameObject* Parrent)
			: VisibleObject(id_object, coordinate_centre, offset_sprite_coordinate,
				texture, frame_count_x, frame_count_y) {
	this->SetLifeLevel(life_level);
	this->CollisionOn();
	max_collision_distance_ = 0;
	Parrent_ = Parrent;
}

void GameObject::SetLifeLevel(int const& life_level, bool const& add_to_previous) {
	int new_life_level;
	if (add_to_previous)	new_life_level = life_level_ + life_level;
	else					new_life_level = life_level;
	if (new_life_level < 0)	new_life_level = 0;

	if (life_level_ != new_life_level) {
		if (new_life_level == 0)	this->PlayAnimateDie();
		if (life_level_ == 0)		this->PlayAnimateLife();

		life_level_ = new_life_level;
	}
}

void GameObject::SetTimeToRespawn(float const& time_to_respawn, bool const& add_to_previous) {
	float new_time_to_respawn;
	if (add_to_previous)	new_time_to_respawn = time_to_respawn_ + time_to_respawn;
	else					new_time_to_respawn = time_to_respawn;
	if (new_time_to_respawn < 0)	new_time_to_respawn = 0;
	time_to_respawn_ = new_time_to_respawn;
}

int GameObject::GetLifeLevel() { return life_level_; }

float GameObject::GetTimeToRespawn() { return time_to_respawn_; }

float GameObject::GetSafeDistance(){
	return max_collision_distance_;
}

GameObject* GameObject::GetPerrent() { return Parrent_; }

void GameObject::RestoreLife() { this->SetLifeLevel(1); }

void GameObject::RecalculateState(float const& game_time) {
	if (time_to_respawn_ != 0) {
		if (time_to_respawn_ > 0) time_to_respawn_ -= game_time;
		else time_to_respawn_ = 0;
	}
}

void GameObject::PlayAnimateDie() { }

void GameObject::PlayAnimateLife() { }

void GameObject::AddCollision(RoundCollision* New_colision) {
	if (New_colision != nullptr) {
		Collisions_.push_back(New_colision);
		float temp = powf(New_colision->GetCoordinate().x, 2) +
					 powf(New_colision->GetCoordinate().y, 2);
		if (temp > 0) temp = sqrtf(temp);
		temp += New_colision->GetRadius();
		if (temp > max_collision_distance_) max_collision_distance_ = temp;
	}
}

bool GameObject::ObjectInRangeLevel(int level_size_x, int level_size_y, int level_size_border){
	if (this->GetCoordinateCentre().x - max_collision_distance_
		> level_size_border &&
		this->GetCoordinateCentre().y - max_collision_distance_
		> level_size_border &&
		this->GetCoordinateCentre().x + max_collision_distance_
		< level_size_x - level_size_border &&
		this->GetCoordinateCentre().y + max_collision_distance_
		< level_size_y - level_size_border)
		return true;

	for (int i = 0; i < (int)this->Collisions_.size(); i++) {
		point_1 = this->Collisions_[i]->
			GetCoordinateByRotation(this->CalculateGradus());
		point_1.x += this->GetCoordinateCentre().x;
		point_1.y *= -1;
		point_1.y += this->GetCoordinateCentre().y;
		if (point_1.x - this->Collisions_[i]->GetRadius()
				< level_size_border ||
			point_1.y - this->Collisions_[i]->GetRadius()
				< level_size_border ||
			point_1.x + this->Collisions_[i]->GetRadius()
				> level_size_x - level_size_border ||
			point_1.y + this->Collisions_[i]->GetRadius()
				> level_size_y - level_size_border) 
			return false;		
	}
	return true;
}

float GameObject::SafeDistanceToCollision(GameObject* Game_object) {
	if (collision_off_ || Game_object->collision_off_) return 100000;

	return this->GetDistanceToPoint(Game_object->GetCoordinateCentre()) -
		this->max_collision_distance_ - Game_object->max_collision_distance_;
}

//not have collision - return true
bool GameObject::Collision(GameObject* Game_object,	bool healt) {
	if (collision_off_ || Game_object->collision_off_) return true;
	float distance;
	if (Game_object != nullptr) {
		for (int i = 0; i < (int)this->Collisions_.size(); i++) {
			point_1 = this->Collisions_[i]->
				GetCoordinateByRotation(this->CalculateGradus());
			point_1.x += this->GetCoordinateCentre().x;
			point_1.y *= -1;
			point_1.y += this->GetCoordinateCentre().y;
			for (int j = 0; j < (int)Game_object->Collisions_.size(); j++) {
				point_2 = Game_object->Collisions_[j]->
					GetCoordinateByRotation(Game_object->CalculateGradus());
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
		}
	}
	return true;
}

void GameObject::CollisionOff() { collision_off_ = true; }

void GameObject::CollisionOn() { collision_off_ = false; }

GameObject::~GameObject() {
	for (int i = 0; i < (int)Collisions_.size(); i++)
		if (Collisions_.at(i)) delete Collisions_[i];
}