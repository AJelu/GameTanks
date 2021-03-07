#include "levels.h"

BaseLevel::BaseLevel()
{
	size_level_width_ = SCREEN_RESOLUTION_X;
	size_level_height_ = SCREEN_RESOLUTION_Y;
}

View& BaseLevel::Draw(RenderWindow& window)
{
	window.draw(Sprite_background_);

	int i;
	for (i = 0; i < Statis_objects_.size(); i++) 
	{ Statis_objects_[i]->Draw(window, nullptr); }
	
	for (i = 0; i < Enemy_objects_.size(); i++)
	{ Enemy_objects_[i]->Draw(window, nullptr); }

	for (i = 0; i < Players_objects_.size(); i++)
	{ Players_objects_[i]->Draw(window, nullptr); }
	
	for (i = 0; i < Shot_objects_.size(); i++)
	{ Shot_objects_[i]->Draw(window, nullptr); }

	for (i = 0; i < Ui_objects_.size(); i++)
	{ Ui_objects_[i]->Draw(window, nullptr); }

	CameraControl();

	window.draw(Sprite_border_);

	return Player_camera;

}

void BaseLevel::AddUiObject(UiObject* Ui_object)
{ if (Ui_object != nullptr) { Ui_objects_.push_back(Ui_object); } }
void BaseLevel::AddStatisObject(GameObject* Static_objects)
{ if (Static_objects != nullptr) { Statis_objects_.push_back(Static_objects); } }
void BaseLevel::AddEnemyObject(TankObject* Enemy_objects)
{ if (Enemy_objects != nullptr) { Enemy_objects_.push_back(Enemy_objects); } }
void BaseLevel::AddPlayerObject(TankObject* Player_objects)
{ if (Player_objects != nullptr) { Players_objects_.push_back(Player_objects); } }
void BaseLevel::AddShotObject(MovebleObject* Shot_objects)
{ if (Shot_objects != nullptr) { Shot_objects_.push_back(Shot_objects); } }

void BaseLevel::SetWatchObject(VisibleObject* Watch_object)
{ if (Watch_object != nullptr) { Watch_object_ = Watch_object; } }

void BaseLevel::SetBackgroundTexture(string texture_address)
{
	Texture_background_.loadFromFile(texture_address);
	Sprite_background_.setTexture(Texture_background_);
	Sprite_background_.setPosition(0, 0);
	size_level_width_ = Texture_background_.getSize().x;
	size_level_height_ = Texture_background_.getSize().y;
}

void BaseLevel::SetBorderTexture(string texture_address)
{
	Texture_border_.loadFromFile(texture_address);
	Sprite_border_.setTexture(Texture_border_);
	Sprite_border_.setPosition(0, 0);
}

BaseObject* BaseLevel::GetObjectToSendClient()
{
	return nullptr;
}

void BaseLevel::RecvObjectFromServer()
{
}

bool BaseLevel::InputKeyboard(int player_nuber, sf::Keyboard::Key Key)
{
	if (player_nuber >= 0 && player_nuber < Players_objects_.size()) {
		if (Key == Keyboard::Up) {
			Players_objects_[player_nuber]->MoveUp();
		}
		if (Key == Keyboard::Down) {
			Players_objects_[player_nuber]->MoveDown();
		}
		if (Key == Keyboard::Left) {
			Players_objects_[player_nuber]->MoveLeft();
		}
		if (Key == Keyboard::Right) {
			Players_objects_[player_nuber]->MoveRight();
		}
		if (Key == Keyboard::Space) {
			this->AddShotObject(Players_objects_[player_nuber]->CreateShot());
			//start test code: explosions
			Statis_objects_[0]->StartPlayAnimation(1, 1, 10, 70);
			Statis_objects_[1]->StartPlayAnimation(1, 1, 48, 20);
			Statis_objects_[2]->StartPlayAnimation(1, 1, 48, 20);
			//end test code;
		}
		return true;
	}
	return false;
}

bool BaseLevel::InputMouse(sf::Event::EventType event_type, sf::Vector2i mpuse_position)
{
	return true;
}

void BaseLevel::InputEnemy()
{
}

bool BaseLevel::UpdateState(float& game_timer)
{
	int i;
	for (i = 0; i < Statis_objects_.size(); i++)
	{ Statis_objects_[i]->ForAnimation(game_timer); }

	for (i = 0; i < Enemy_objects_.size(); i++)
	{
		Enemy_objects_[i]->RecalculateState(game_timer);
		Enemy_objects_[i]->ForAnimation(game_timer);
	}

	for (i = 0; i < Players_objects_.size(); i++)
	{
		Players_objects_[i]->RecalculateState(game_timer);
		Players_objects_[i]->ForAnimation(game_timer);
	}

	for (i = 0; i < Shot_objects_.size(); i++)
	{
		Shot_objects_[i]->RecalculateState(game_timer);
		Shot_objects_[i]->ForAnimation(game_timer);
	}

	for (i = 0; i < Ui_objects_.size(); i++)
	{ Ui_objects_[i]->ForAnimation(game_timer); }

	this->CalculateCollisionOnLevel();
	//respawn died objects and delete from vector
	// 

	return true;
}

void BaseLevel::CalculateCollisionOnLevel()
{
	bool recalc_i, recalc_all = true;
	int i, j;
	while (recalc_all) {
		recalc_all = false;

		//collisions for players
		for (i = 0; i < Players_objects_.size(); i++) {
			recalc_i = false;
			for (j = 0; j < Statis_objects_.size(); j++) {
				if (Players_objects_[i]->SafeDistanceToCollision(Statis_objects_[j]) < 0) {
					if (!Players_objects_[i]->Collision(Statis_objects_[j], true)) {
						j = -1;
						recalc_i = true;
						continue;
					}
				}
			}

			for (j = i + 1; j < Players_objects_.size(); j++) {
				if (Players_objects_[i]->SafeDistanceToCollision(Players_objects_[j]) < 0) {
					if (!Players_objects_[i]->Collision(Players_objects_[j], true)) {
						j = i;
						recalc_i = true;
						continue;
					}
				}
			}

			for (j = 0; j < Enemy_objects_.size(); j++) {
				if (Players_objects_[i]->SafeDistanceToCollision(Enemy_objects_[j]) < 0) {
					if (!Players_objects_[i]->Collision(Enemy_objects_[j], true)) {
						j = -1;
						recalc_i = true;
						continue;
					}
				}
			}

			if (recalc_i) {
				i = -1;
				recalc_all = true;
				continue;
			}
		}
		//collisions for enemys
		for (i = 0; i < Enemy_objects_.size(); i++) {
			recalc_i = false;
			for (j = 0; j < Statis_objects_.size(); j++) {
				if (Enemy_objects_[i]->SafeDistanceToCollision(Statis_objects_[j]) < 0) {
					if (!Enemy_objects_[i]->Collision(Statis_objects_[j], true)) {
						j = -1;
						recalc_i = true;
						continue;
					}
				}
			}

			for (j = 0; j < Players_objects_.size(); j++) {
				if (Enemy_objects_[i]->SafeDistanceToCollision(Players_objects_[j]) < 0) {
					if (!Enemy_objects_[i]->Collision(Players_objects_[j], true)) {
						j = -1;
						recalc_i = true;
						continue;
					}
				}
			}
			
			for (j = i + 1; j < Enemy_objects_.size(); j++) {
				if (Enemy_objects_[i]->SafeDistanceToCollision(Enemy_objects_[j]) < 0) {
					if (!Enemy_objects_[i]->Collision(Enemy_objects_[j], true)) {
						j = i;
						recalc_i = true;
						continue;
					}
				}
			}
			if (recalc_i) {
				i = -1;
				recalc_all = true;
				continue;
			}
		}
	}


	//shot collisions
	for (i = 0; i < Shot_objects_.size(); i++) {
		for (j = 0; j < Enemy_objects_.size(); j++) {
			if (Shot_objects_[i]->SafeDistanceToCollision(Enemy_objects_[j]) < 0) {
				if (!Shot_objects_[i]->Collision(Enemy_objects_[j], false)) {
					//add Enemy_objects_[j] to vector Dies_objects_ and play dies
				}
			}
		}

		for (j = 0; j < Players_objects_.size(); j++) {
			if (Shot_objects_[i]->SafeDistanceToCollision(Players_objects_[j]) < 0) {
				if (!Shot_objects_[i]->Collision(Players_objects_[j], false)) {
					//add Players_objects_[j] to vector Dies_objects_ and play dies
				}
			}
		}

		for (j = 0; j < Statis_objects_.size(); j++) {
			if (Shot_objects_[i]->SafeDistanceToCollision(Statis_objects_[j]) < 0) {
				if (!Shot_objects_[i]->Collision(Statis_objects_[j], false)) {
					//add Statis_objects_[j] to vector Dies_objects_ and play dies
				}
			}
		}
	}

	for (i = 0; i < Enemy_objects_.size(); i++) {
		Enemy_objects_[i]->SafeState();
	}

	for (i = 0; i < Players_objects_.size(); i++) {
		Players_objects_[i]->SafeState();
	}

	for (i = 0; i < Statis_objects_.size(); i++) {
		Statis_objects_[i]->SafeState();
	}
}

void BaseLevel::CameraControl()
{
	float temp_camera_x, temp_camera_y;
	if (Watch_object_ != nullptr) {
		temp_camera_x = Watch_object_->GetCoordinateCentre().x;
		temp_camera_y = Watch_object_->GetCoordinateCentre().y;
	}
	else {
		temp_camera_x = size_level_width_ / 2;
		temp_camera_y = size_level_height_ / 2;
	}

	if (temp_camera_x < SCREEN_RESOLUTION_X / 2) 
		temp_camera_x = SCREEN_RESOLUTION_X / 2; //left edge
	if (temp_camera_x > size_level_width_ - SCREEN_RESOLUTION_X / 2) 
		temp_camera_x = size_level_width_ - SCREEN_RESOLUTION_X / 2; //right edge
	if (temp_camera_y < SCREEN_RESOLUTION_Y / 2) 
		temp_camera_y = SCREEN_RESOLUTION_Y / 2; //upper edge
	if (temp_camera_y > size_level_height_ - SCREEN_RESOLUTION_Y / 2) 
		temp_camera_y = size_level_height_ - SCREEN_RESOLUTION_Y / 2; //lower edge

	Player_camera.setSize(SCREEN_RESOLUTION_X, SCREEN_RESOLUTION_Y);

	Player_camera.setCenter(temp_camera_x, temp_camera_y);
}

int BaseLevel::NextLevel()
{
	return 0;
}

bool BaseLevel::ExitGame()
{
	return false;
}

BaseLevel::~BaseLevel()
{
	int i;
	for (i = 0; i < Ui_objects_.size(); i++) {
		if (Ui_objects_.at(i)) delete Ui_objects_[i];
	}
	for (i = 0; i < Statis_objects_.size(); i++) {
		if (Statis_objects_.at(i)) delete Statis_objects_[i];
	}
	for (i = 0; i < Enemy_objects_.size(); i++) {
		if (Enemy_objects_.at(i)) delete Enemy_objects_[i];
	}
	for (i = 0; i < Players_objects_.size(); i++) {
		if (Players_objects_.at(i)) delete Players_objects_[i];
	}
	for (i = 0; i < Shot_objects_.size(); i++) {
		if (Shot_objects_.at(i)) delete Shot_objects_[i];
	}
}
