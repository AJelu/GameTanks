#include "objects.h"
#include <cmath>

GameObject::GameObject() : AudioObject() {
	this->SetLifeLevel(1);
	this->SetMaxLifeLevel(1);
	this->CollisionOn();
	max_collision_distance_ = 0;
	Parrent_ = nullptr;
}

GameObject::GameObject(int const& id_object,
			sf::Vector2f const& coordinate_centre,
			sf::Vector2f const& offset_sprite_coordinate,
			std::string const& texture, 
			int const& frame_count_x, int const& frame_count_y,
			int const& max_life_level, GameObject* Parrent)
			: AudioObject(id_object, coordinate_centre, offset_sprite_coordinate,
				texture, frame_count_x, frame_count_y) {
	this->SetLifeLevel(max_life_level);
	this->SetMaxLifeLevel(max_life_level);
	this->CollisionOn();
	max_collision_distance_ = 0;
	Parrent_ = Parrent;
}

void GameObject::SetLifeLevel(int const& life_level, bool const& add_to_previous) {
	int new_life_level;
	if (add_to_previous)	new_life_level = life_level_ + life_level;
	else					new_life_level = life_level;
	if (new_life_level < 0)	new_life_level = 0;
	if (new_life_level > max_life_level_) new_life_level = max_life_level_;

	if (life_level_ != new_life_level) {
		if (new_life_level == 0)	this->ActionDie();
		else if (life_level_ == 0)	this->ActionLife();
		else						this->ActionChangeLifeLevel(new_life_level);

		life_level_ = new_life_level;
	}
}

void GameObject::SetMaxLifeLevel(int const& max_life_level) {
	if (max_life_level > 0) {
		max_life_level_ = max_life_level;
		if (max_life_level_ > this->GetLifeLevel()) this->SetLifeLevel(max_life_level_);
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

int GameObject::GetMaxLifeLevel() { return max_life_level_; }

float GameObject::GetTimeToRespawn() { return time_to_respawn_; }

float GameObject::GetSafeDistance(){
	return max_collision_distance_;
}

GameObject* GameObject::GetPerrent() { return Parrent_; }

void GameObject::SetBasePoint(int const& base_point) { base_point_ = base_point; }

void GameObject::SetCurrentPoint(int const& current_point, bool const& add_to_previous) {
	if (add_to_previous)	current_point_ += current_point;
	else					current_point_ = current_point;
	if (current_point_ < 0) current_point_ = 0;
}

void GameObject::RestoreLife() { this->SetLifeLevel(max_life_level_); }

void GameObject::RecalculateState(float const& game_time) {
	AudioObject::RecalculateState(game_time);
	if (time_to_respawn_ != 0)
		if (time_to_respawn_ > 0)	time_to_respawn_ -= game_time;
		else						time_to_respawn_ = 0;
}

int GameObject::GetBasePoint() { return base_point_; }

int GameObject::GetCurrentPoint() { return current_point_; }

void GameObject::ActionDie() { }

void GameObject::ActionChangeLifeLevel(int const& life_level) { }

void GameObject::ActionLife() { }

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
	if (this->GetCoordinateCentre().x - this->GetSafeDistance()
		> level_size_border &&
		this->GetCoordinateCentre().y - this->GetSafeDistance()
		> level_size_border &&
		this->GetCoordinateCentre().x + this->GetSafeDistance()
		< level_size_x - level_size_border &&
		this->GetCoordinateCentre().y + this->GetSafeDistance()
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
	if (collision_off_ || Game_object->collision_off_) return 10000000;

	return this->GetDistanceToPoint(Game_object->GetCoordinateCentre()) -
		this->GetSafeDistance() - Game_object->GetSafeDistance();
}

//not have collision - return true
bool GameObject::Collision(GameObject* Game_object) {
	if (Game_object != nullptr) {
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
						return false;
					}
				}
			}
		}		
	}
	return true;
}

void GameObject::CollisionOff() { collision_off_ = true; }

void GameObject::CollisionOn() { collision_off_ = false; }

std::string GameObject::GetGameType() { return game_type_; }

void GameObject::SetGameType(std::string const& game_type) { game_type_ = game_type; }

std::string GameObject::ClassName() { return "GameObject"; }

bool GameObject::CreatePacket(sf::Packet& Packet) {
	AudioObject::CreatePacket(Packet);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="Packet"></param>
	/// <returns></returns>
	return false;
}

bool GameObject::SetDataFromPacket(sf::Packet& Packet) {
	AudioObject::SetDataFromPacket(Packet);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="Packet"></param>
	/// <returns></returns>
	return false;
}

GameObject::~GameObject() {
	for (int i = 0; i < (int)Collisions_.size(); i++) {
		if (Collisions_.at(i)) delete Collisions_[i];
		Collisions_[i] = nullptr;
	}
	Parrent_ = nullptr;
}