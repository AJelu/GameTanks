#include "objects.h"
#include <cmath>

bool GameObject::display_collision_;

GameObject::GameObject() : AudioObject() {
	this->SetMaxLifeLevel(1);
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
			int const& max_life_level, GameObject* Parrent)
			: AudioObject(id_object, coordinate_centre, offset_sprite_coordinate,
				texture, frame_count_x, frame_count_y) {
	this->SetMaxLifeLevel(max_life_level);
	this->SetLifeLevel(max_life_level);
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
		this->SetNeedSynchByLan(true);
	}
}

void GameObject::SetMaxLifeLevel(int const& max_life_level) {
	if (max_life_level > 0) {
		max_life_level_ = max_life_level;
		if (max_life_level_ < this->GetLifeLevel()) 
			this->SetLifeLevel(max_life_level_);
		this->SetNeedSynchByLan(true);
	}
}

void GameObject::SetTimeToRespawn(float const& time_to_respawn, 
		bool const& add_to_previous) {
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

bool GameObject::DisplayCollision(bool const& display_collision) {
	display_collision_ = display_collision;
	return display_collision_;
}

void GameObject::SetBasePoint(int const& base_point) { 
	base_point_ = base_point;
	this->SetNeedSynchByLan(true);
}

void GameObject::SetCurrentPoint(int const& current_point, 
		bool const& add_to_previous) {
	if (add_to_previous)	current_point_ += current_point;
	else					current_point_ = current_point;
	if (current_point_ < 0) current_point_ = 0;
	this->SetNeedSynchByLan(true);
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

bool GameObject::ObjectInRangeLevel(int level_size_x, int level_size_y, 
		int level_size_border) {
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
		Point_1_ = this->Collisions_[i]->
			GetCoordinateByRotation(this->CalculateGradus());
		Point_1_.x += this->GetCoordinateCentre().x;
		Point_1_.y *= -1;
		Point_1_.y += this->GetCoordinateCentre().y;
		if (Point_1_.x - this->Collisions_[i]->GetRadius()
				< level_size_border ||
			Point_1_.y - this->Collisions_[i]->GetRadius()
				< level_size_border ||
			Point_1_.x + this->Collisions_[i]->GetRadius()
				> level_size_x - level_size_border ||
			Point_1_.y + this->Collisions_[i]->GetRadius()
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

//If dont have collision - return true
bool GameObject::Collision(GameObject* Game_object) {
	if (Game_object != nullptr) {
		if (collision_off_ || Game_object->collision_off_) return true;
		float distance;
		if (Game_object != nullptr) {
			for (int i = 0; i < (int)this->Collisions_.size(); i++) {
				Point_1_ = this->Collisions_[i]->
					GetCoordinateByRotation(this->CalculateGradus());
				Point_1_.x += this->GetCoordinateCentre().x;
				Point_1_.y *= -1;
				Point_1_.y += this->GetCoordinateCentre().y;
				for (int j = 0; j < (int)Game_object->Collisions_.size(); j++) {
					Point_2_ = Game_object->Collisions_[j]->
						GetCoordinateByRotation(Game_object->CalculateGradus());
					Point_2_.x += Game_object->GetCoordinateCentre().x;
					Point_2_.y *= -1;
					Point_2_.y += Game_object->GetCoordinateCentre().y;

					distance = sqrtf(powf(Point_1_.x - Point_2_.x, 2) +
						powf(Point_1_.y - Point_2_.y, 2));
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

int GameObject::GetGameType() { return game_type_; }

void GameObject::SetGameType(int const& game_type) { 
	game_type_ = game_type;
	this->SetNeedSynchByLan(true);
}

std::string GameObject::ClassName() { return "GameObject"; }

bool GameObject::CreatePacket(sf::Packet& Packet) {
	bool result = AudioObject::CreatePacket(Packet);
	Packet << life_level_ << max_life_level_ << base_point_ << current_point_;
	Packet << game_type_;
	return result;
}

bool GameObject::SetDataFromPacket(sf::Packet& Packet) {
	if (AudioObject::SetDataFromPacket(Packet)) {
		Packet >> life_level_ >> max_life_level_ >> base_point_ >> current_point_;
		if (life_level_ > max_life_level_) {
			life_level_ = max_life_level_;
			return false;
		}
		if (life_level_ < 0 || max_life_level_ < 0) return false;
		Packet >> game_type_;
		return true;
	}
	return false;
}

void GameObject::Draw(sf::RenderWindow& window) {
	AudioObject::Draw(window);
	if (display_collision_) {
		for (int i = 0; i < (int)Collisions_.size(); i++) {
			sf::CircleShape shape(Collisions_[i]->GetRadius());
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineThickness(1);
			shape.setOutlineColor(sf::Color::Red);
			Point_1_ = this->Collisions_[i]->
				GetCoordinateByRotation(this->CalculateGradus());
			Point_1_.x += this->GetCoordinateCentre().x - Collisions_[i]->GetRadius();
			Point_1_.y *= -1;
			Point_1_.y += this->GetCoordinateCentre().y - Collisions_[i]->GetRadius();
			shape.setPosition(Point_1_);
			window.draw(shape);
		}
	}
}

GameObject::~GameObject() {
	for (int i = 0; i < (int)Collisions_.size(); i++) delete Collisions_[i];
}