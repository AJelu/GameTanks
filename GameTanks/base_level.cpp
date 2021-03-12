#include "levels.h"

BaseLevel::BaseLevel() {
	size_level_width_ = SCREEN_RESOLUTION_X;
	size_level_height_ = SCREEN_RESOLUTION_Y;
}

sf::View& BaseLevel::Draw(sf::RenderWindow& window) {
	window.draw(Sprite_background_);
	int i;
	for (i = 0; i < (int)Static_objects_.size(); i++)	Static_objects_[i]->Draw(window);	
	for (i = 0; i < (int)Enemy_objects_.size(); i++)	Enemy_objects_[i]->Draw(window);
	for (i = 0; i < (int)Players_objects_.size(); i++)	Players_objects_[i]->Draw(window);
	//for (i = 0; i < (int)Shot_objects_.size(); i++)		Shot_objects_[i]->Draw(window);
	for (MovebleObject* item : Shot_objects_)			item->Draw(window);
	for (i = 0; i < (int)Ui_objects_.size(); i++)		Ui_objects_[i]->Draw(window);
	CameraControl();
	window.draw(Sprite_border_);
	return Player_camera_;
}

bool BaseLevel::AddUiObject(UiObject* Ui_object) {
	if (Ui_object != nullptr) {
		Ui_objects_.push_back(Ui_object);
		return true;
	}
	return false;
}

bool BaseLevel::AddStaticObject(GameObject* Static_objects) {
	if (Static_objects != nullptr && this->RespawnObject(Static_objects)) {
		Static_objects->SafeState();
		Static_objects_.push_back(Static_objects);
		return true;
	}
	return false;
}

bool BaseLevel::AddEnemyObject(TankObject* Enemy_objects) {
	if (Enemy_objects != nullptr && this->RespawnObject(Enemy_objects)) {
		Enemy_objects->SafeState();
		Enemy_objects_.push_back(Enemy_objects);
		enemy_shot_time_.push_back(0);
		Enemy_objects = nullptr;
		return true;
	}
	return false;
}

bool BaseLevel::AddPlayerObject(TankObject* Player_objects) {
	if (Player_objects != nullptr && this->SafePointSpawn(Player_objects)) {
		Players_objects_.push_back(Player_objects);
		return true;
	}
	return false;
}

bool BaseLevel::AddShotObject(MovebleObject* Shot_objects) {
	if (Shot_objects != nullptr) {
		Shot_objects_.push_back(Shot_objects);
		Shot_objects = nullptr;
		return true;
	}
	return false;
}

bool BaseLevel::AddDieObject(GameObject* Dies_objects) {
	if (Dies_objects != nullptr && Dies_objects->GetLifeLevel() == 0) {
		Dies_objects->SetTimeToRespawn(TIME_TO_RESPAWN);
		Dies_objects_.push_back(Dies_objects);
		Dies_objects = nullptr;
		return true;
	}
	Dies_objects = nullptr;
	return false;
}

bool BaseLevel::SetWatchObject(VisibleObject* Watch_object) { 
	if (Watch_object != nullptr) {
		Watch_object_ = Watch_object;
		Watch_object = nullptr;
		return true;
	}
	return false;
}

void BaseLevel::SetBackgroundTexture(std::string texture_address) {
	Texture_background_.loadFromFile(texture_address);
	Sprite_background_.setTexture(Texture_background_);
	Sprite_background_.setPosition(0, 0);
}

void BaseLevel::SetBorderTexture(std::string texture_address, int const& size_level_border) {
	Texture_border_.loadFromFile(texture_address);
	Sprite_border_.setTexture(Texture_border_);
	Sprite_border_.setPosition(0, 0);
	size_level_width_ = Texture_border_.getSize().x;
	size_level_height_ = Texture_border_.getSize().y;
	size_level_border_ = size_level_border_;
}

BaseObject* BaseLevel::GetObjectToSendClient() {
	return nullptr; /////////////////////////////////////////////////////////////////////////
}

void BaseLevel::RecvObjectFromServer() {
	////////////////////////////////////////////////////////////////////////////////////////
}

bool BaseLevel::InputKeyboard(int const& player_number, sf::Keyboard::Key Key) {
	if (player_number >= 0 && player_number < (int)Players_objects_.size()) {
		if (Key == sf::Keyboard::Up) Players_objects_[player_number]->MoveUp();
		if (Key == sf::Keyboard::Down) Players_objects_[player_number]->MoveDown();
		if (Key == sf::Keyboard::Left) Players_objects_[player_number]->MoveLeft();
		if (Key == sf::Keyboard::Right) Players_objects_[player_number]->MoveRight();
		if (Key == sf::Keyboard::Space)
			this->AddShotObject(Players_objects_[player_number]->CreateShot());
		return true;
	}
	return false;
}

bool BaseLevel::InputMouse(sf::Event::EventType event_type, sf::Vector2i mpuse_position) {
	return true;//////////////////////////////////////////////////////////////////////////////
}

void BaseLevel::InputEnemy() {
	for (int i = 0; i < (int)Enemy_objects_.size(); i++) {
		if (Enemy_objects_[i]->GetDistanceMove() <= 0 &&
			Enemy_objects_[i]->GetRotationDegree() == 0) { //for moving enemy
			if (rand() % 5 == 0) Enemy_objects_[i]->
					SetRotationDegree((rand() % ENEMY_ROTATION_DEGREE)
						- ENEMY_ROTATION_DEGREE / 2);
			else Enemy_objects_[i]->
					SetDistanceMove((rand() % ENEMY_DISTANCE_MOVE) - 5);
		}
		if (enemy_shot_time_[i] <= 0) { //for shooting enemy
			this->AddShotObject(Enemy_objects_[i]->CreateShot());
			enemy_shot_time_[i] = Enemy_objects_[i]->GetTimeFreezeShot() +
				rand() % int(Enemy_objects_[i]->GetTimeFreezeShot()
					* ENEMY_SHOT_TIME_MULTIPLY);
		}
	}
}

bool BaseLevel::UpdateState(float& game_timer) {
	int i;
	// update animation for Static_objects_
	for (i = 0; i < (int)Static_objects_.size(); i++) {
		Static_objects_[i]->RecalculateState(game_timer);
		Static_objects_[i]->ForAnimation(game_timer);
	}
	// update animation and state for Enemy_objects_
	for (i = 0; i < (int)Enemy_objects_.size(); i++) {
		Enemy_objects_[i]->RecalculateState(game_timer);
		Enemy_objects_[i]->ForAnimation(game_timer);
		enemy_shot_time_[i] -= game_timer;
	}
	// update animation and state for Players_objects_
	for (i = 0; i < (int)Players_objects_.size(); i++) {
		Players_objects_[i]->RecalculateState(game_timer);
		Players_objects_[i]->ForAnimation(game_timer);
	}
	// update animation and state for Shot_objects_
	/*for (i = 0; i < (int)Shot_objects_.size(); i++) {
		Shot_objects_[i]->RecalculateState(game_timer);
		Shot_objects_[i]->ForAnimation(game_timer);
	}*/
	for (MovebleObject* item : Shot_objects_){
		item->RecalculateState(game_timer);
		item->ForAnimation(game_timer);
	}
	// update animation for Ui_objects_
	for (i = 0; i < (int)Ui_objects_.size(); i++)
		Ui_objects_[i]->ForAnimation(game_timer);

	this->CalculateCollisionOnLevel();

	for (i = 0; i < (int)Dies_objects_.size(); i++) {
		if (Dies_objects_[i]->GetTimeToRespawn() == 0) {
			Dies_objects_[i]->RestoreLife();
			Dies_objects_[i]->CollisionOn();
			if (this->RespawnObject(Dies_objects_[i])) {
				//Dies_objects_[i]->SafeState();
				Dies_objects_[i] = nullptr;
				Dies_objects_.erase(Dies_objects_.begin() + i);
				i--;
			}
		}
	}

	return true;
}

void BaseLevel::CalculateCollisionOnLevel() {
	bool recalc_i, recalc_all = true;
	int i, j, control1 = 0, control2 = 0;
	while (recalc_all) {
		recalc_all = false;
		control1++;
		if (control1 > 100000) {
			std::cout << "control1 = " << control1 
				<< "; exit recalc_all CalculateCollisionOnLevel();" << std::endl;
			break;
		}
		//collisions for players
		for (i = 0; i < (int)Players_objects_.size(); i++) {
			recalc_i = false;
			control2 = 0;
			if (Players_objects_[i]->ObjectInRangeLevel(
				size_level_width_, size_level_height_, size_level_border_)) {
				for (j = 0; j < (int)Static_objects_.size(); j++) {
					if (Players_objects_[i]->SafeDistanceToCollision(Static_objects_[j]) < 0) {
						if (!Players_objects_[i]->Collision(Static_objects_[j], true)) {
							j = -1;
							recalc_i = true;
							control2++;
							if (control2 > 100000) {
								std::cout << "control2 = " << control2
									<< "; exit recalc_i Players_objects_ <-> Static_objects_;"
									<< std::endl;
								break;
							}
							continue;
						}
					}
				}

				control2 = 0;
				for (j = i + 1; j < (int)Players_objects_.size(); j++) {
					if (Players_objects_[i]->SafeDistanceToCollision(Players_objects_[j]) < 0) {
						if (!Players_objects_[i]->Collision(Players_objects_[j], true)) {
							j = i;
							recalc_i = true;
							control2++;
							if (control2 > 100000) {
								std::cout << "control2 = " << control2
									<< "; exit recalc_i Players_objects_ <-> Players_objects_;"
									<< std::endl;
								break;
							}
							continue;
						}
					}
				}

				control2 = 0;
				for (j = 0; j < (int)Enemy_objects_.size(); j++) {
					if (Players_objects_[i]->SafeDistanceToCollision(Enemy_objects_[j]) < 0) {
						if (!Players_objects_[i]->Collision(Enemy_objects_[j], true)) {
							Enemy_objects_[j]->SetDistanceMove(-10);
							j = -1;
							recalc_i = true;
							control2++;
							if (control2 > 100000) {
								std::cout << "control2 = " << control2
									<< "; exit recalc_i Players_objects_ <-> Enemy_objects_;"
									<< std::endl;
								break;
							}
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
			else {
				Players_objects_[i]->RestorePreviousState();
				i = -1;
				recalc_all = true;
				continue;
			}
		}
		//collisions for enemys
		for (i = 0; i < (int)Enemy_objects_.size(); i++) {
			recalc_i = false;
			control2 = 0;
			if (Enemy_objects_[i]->ObjectInRangeLevel(
				size_level_width_, size_level_height_, size_level_border_)) {
				for (j = 0; j < (int)Static_objects_.size(); j++) {
					if (Enemy_objects_[i]->SafeDistanceToCollision(Static_objects_[j]) < 0) {
						if (!Enemy_objects_[i]->Collision(Static_objects_[j], true)) {
							Enemy_objects_[i]->SetDistanceMove(-50);
							j = -1;
							recalc_i = true;
							control2++;
							if (control2 > 100000) {
								std::cout << "control2 = " << control2
									<< "; exit recalc_i Enemy_objects_ <-> Static_objects_;"
									<< std::endl;
								break;
							}
							continue;
						}
					}
				}

				control2 = 0;
				for (j = i + 1; j < (int)Enemy_objects_.size(); j++) {
					if (Enemy_objects_[i]->SafeDistanceToCollision(Enemy_objects_[j]) < 0) {
						if (!Enemy_objects_[i]->Collision(Enemy_objects_[j], true)) {
							Enemy_objects_[i]->SetDistanceMove(-50);
							j = i;
							recalc_i = true;
							control2++;
							if (control2 > 100000) {
								std::cout << "control2 = " << control2
									<< "; exit recalc_i Enemy_objects_ <-> Enemy_objects_;"
									<< std::endl;
								break;
							}
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
			else {
				Enemy_objects_[i]->RestorePreviousState();
				Enemy_objects_[i]->SetDistanceMove(-50);
				i = -1;
				recalc_all = true;
				continue;
			}
		}
	}
	

	//shot collisions
	bool die_current_shot;
	for (MovebleObject* Shot_item : Shot_objects_){
		//check if shot is die
		if (Shot_item->GetLifeLevel() > 0) {
			// shot is not die
			die_current_shot = false;
			for (j = 0; j < (int)Enemy_objects_.size(); j++) {				
				if (Shot_item->GetPerrent() != Enemy_objects_[j] && //check if not parent
					Shot_item->SafeDistanceToCollision(Enemy_objects_[j]) < 0) {
					if (!Shot_item->Collision(Enemy_objects_[j], false)) {
						//add Enemy_objects_[j] to vector Dies_objects_ and play dies
						die_current_shot = true;
						if (Enemy_objects_[j]->GetLifeLevel() != 0) {
							Enemy_objects_[j]->SetLifeLevel(
								-Shot_item->GetLifeLevel(), true);
							if (this->AddDieObject(Enemy_objects_[j])) {
								Enemy_objects_[j]->SetDistanceMove(0);
								Enemy_objects_[j]->SetFreezeTime(TIME_TO_RESPAWN);
							}
						}
					}
				}
			}

			for (j = 0; j < (int)Players_objects_.size(); j++) {
				if (Shot_item->GetPerrent() != Players_objects_[j] && //check if not parent
					Shot_item->SafeDistanceToCollision(Players_objects_[j]) < 0) {
					if (!Shot_item->Collision(Players_objects_[j], false)) {
						//add Players_objects_[j] to vector Dies_objects_ and play dies
						die_current_shot = true;
						if (Players_objects_[j]->GetLifeLevel() != 0) {
							Players_objects_[j]->SetLifeLevel(
								-Shot_item->GetLifeLevel(), true);
							if (this->AddDieObject(Players_objects_[j])) {
								Players_objects_[j]->SetDistanceMove(0);
								Players_objects_[j]->SetFreezeTime(TIME_TO_RESPAWN);
							}
						}
					}
				}
			}

			for (j = 0; j < (int)Static_objects_.size(); j++) {
				if (Shot_item->GetPerrent() != Static_objects_[j] && //check if not parent
					Shot_item->SafeDistanceToCollision(Static_objects_[j]) < 0) {
					if (!Shot_item->Collision(Static_objects_[j], false)) {
						//add Static_objects_[j] to vector Dies_objects_ and play dies
						die_current_shot = true;
						if (Static_objects_[j]->GetLifeLevel() != 0) {
							Static_objects_[j]->SetLifeLevel(
								-Shot_item->GetLifeLevel(), true);
							this->AddDieObject(Static_objects_[j]);
						}
					}
				}
			}
			if (die_current_shot || Shot_item->GetDistanceMove() == 0) {
				Shot_item->SetDistanceMove(0);
				Shot_item->SetLifeLevel(0);
			}
		}
		else {
			//shot is die
			if (Shot_item->AnimationEnd()) {
				delete Shot_item;
				Shot_objects_.remove(Shot_item);
				//i--;
			}
		}
	}
	
	//save good collisions
	for (i = 0; i < (int)Enemy_objects_.size(); i++)	Enemy_objects_[i]->SafeState();
	for (i = 0; i < (int)Players_objects_.size(); i++)	Players_objects_[i]->SafeState();
	for (i = 0; i < (int)Static_objects_.size(); i++)	Static_objects_[i]->SafeState();
}

void BaseLevel::CameraControl() {
	float temp_camera_x, temp_camera_y;
	if (Watch_object_ != nullptr) {
		temp_camera_x = Watch_object_->GetCoordinateCentre().x;
		temp_camera_y = Watch_object_->GetCoordinateCentre().y;
	}
	else {
		temp_camera_x = size_level_width_ / 2.0f;
		temp_camera_y = size_level_height_ / 2.0f;
	}

	if (temp_camera_x < SCREEN_RESOLUTION_X / 2.0f)
		temp_camera_x = SCREEN_RESOLUTION_X / 2.0f; //left edge
	if (temp_camera_x > size_level_width_ - SCREEN_RESOLUTION_X / 2.0f)
		temp_camera_x = size_level_width_ - SCREEN_RESOLUTION_X / 2.0f; //right edge
	if (temp_camera_y < SCREEN_RESOLUTION_Y / 2.0f)
		temp_camera_y = SCREEN_RESOLUTION_Y / 2.0f; //upper edge
	if (temp_camera_y > size_level_height_ - SCREEN_RESOLUTION_Y / 2.0f)
		temp_camera_y = size_level_height_ - SCREEN_RESOLUTION_Y / 2.0f; //lower edge

	Player_camera_.setSize((float)SCREEN_RESOLUTION_X, (float)SCREEN_RESOLUTION_Y);

	Player_camera_.setCenter(temp_camera_x, temp_camera_y);
}

bool BaseLevel::SafePointSpawn(GameObject* Game_object) {
	float level_size;
	float cur_procent;
	if (size_level_height_ > size_level_width_) 
		level_size = float(size_level_height_ - size_level_border_);
	else										
		level_size = float(size_level_width_ - size_level_border_);

	int i;
	// check psition Game_object Static_objects_
	cur_procent = level_size * min_distance_respawn_to_Static_objects_;
	for (i = 0; i < (int)Static_objects_.size(); i++) {
		if (Static_objects_[i] != Game_object)
			if (Game_object->SafeDistanceToCollision(Static_objects_[i]) < cur_procent) 
				return false;
	}
	// check psition Game_object for Enemy_objects_
	cur_procent = level_size * min_distance_respawn_to_Enemy_objects_;
	for (i = 0; i < (int)Enemy_objects_.size(); i++) {
		if (Enemy_objects_[i] != Game_object)
			if (Game_object->SafeDistanceToCollision(Enemy_objects_[i]) < cur_procent)
				return false;
	}

	// check psition Game_object for Players_objects_
	cur_procent = level_size * min_distance_respawn_to_Players_objects_;
	for (i = 0; i < (int)Players_objects_.size(); i++) {
		if (Players_objects_[i] != Game_object)
			if (Game_object->SafeDistanceToCollision(Players_objects_[i]) < cur_procent)
				return false;
	}

	// check psition Game_object for Shot_objects_
	cur_procent = level_size * min_distance_respawn_to_Shot_objects_;
	for (MovebleObject* Shot_item : Shot_objects_) {
		if (Game_object->SafeDistanceToCollision(Shot_item) < cur_procent)
			return false;
	}
	return true;
}

bool BaseLevel::RespawnObject(GameObject* Game_object)
{
	for (int i = 0; i < 100000; i++) {
		Game_object->SetCoordinate(sf::Vector2f(
			size_level_border_ + Game_object->GetSafeDistance() +
			float(rand() % int(size_level_width_
				- (size_level_border_ + Game_object->GetSafeDistance()) * 2)),
			size_level_border_ + Game_object->GetSafeDistance() +
			float(rand() % int(size_level_height_
				- (size_level_border_ + Game_object->GetSafeDistance()) * 2))
		));
		if (this->SafePointSpawn(Game_object)) {
			std::cout << "good respawn: " << i << ";" << std::endl;
			return true;
		}
	}
	std::cout << "error respawn: 100000;" << std::endl;
	Game_object->RestorePreviousState();
	Game_object = nullptr;
	return false;
}

int BaseLevel::NextLevel() {
	return 0; //////////////////////////////////////////////////////////////////
}

bool BaseLevel::ExitGame() {
	return false; //////////////////////////////////////////////////////////////
}

BaseLevel::~BaseLevel() {
	int i;
	for (i = 0; i < (int)Ui_objects_.size(); i++) 
		if (Ui_objects_.at(i)) delete Ui_objects_[i];

	for (i = 0; i < (int)Static_objects_.size(); i++) 
		if (Static_objects_.at(i)) delete Static_objects_[i];

	for (i = 0; i < (int)Enemy_objects_.size(); i++)	
		if (Enemy_objects_.at(i)) delete Enemy_objects_[i];

	for (i = 0; i < (int)Players_objects_.size(); i++)	
		if (Players_objects_.at(i)) delete Players_objects_[i];

	for (MovebleObject* Shot_item : Shot_objects_) delete Shot_item;
}
