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
	for (i = 0; i < (int)Shot_objects_.size(); i++)		Shot_objects_[i]->Draw(window);
	for (i = 0; i < (int)Ui_objects_.size(); i++)		Ui_objects_[i]->Draw(window);
	CameraControl();
	window.draw(Sprite_border_);
	return Player_camera_;
}

void BaseLevel::AddUiObject(UiObject* Ui_object) { 
	if (Ui_object != nullptr) Ui_objects_.push_back(Ui_object);
}

void BaseLevel::AddStaticObject(GameObject* Static_objects) { 
	if (Static_objects != nullptr) Static_objects_.push_back(Static_objects);
}

void BaseLevel::AddEnemyObject(TankObject* Enemy_objects) { 
	if (Enemy_objects != nullptr) Enemy_objects_.push_back(Enemy_objects); 
}

void BaseLevel::AddPlayerObject(TankObject* Player_objects) { 
	if (Player_objects != nullptr) Players_objects_.push_back(Player_objects); 
}

void BaseLevel::AddShotObject(MovebleObject* Shot_objects) {
	if (Shot_objects != nullptr) Shot_objects_.push_back(Shot_objects);
}

void BaseLevel::SetWatchObject(VisibleObject* Watch_object) { 
	if (Watch_object != nullptr) Watch_object_ = Watch_object;
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
		if (Key == sf::Keyboard::Space) {
			this->AddShotObject(Players_objects_[player_number]->CreateShot());
			//start test code: explosions-----------------------------------------------------
			Static_objects_[0]->StartPlayAnimation(1, 1, 10, 50);
			Static_objects_[1]->StartPlayAnimation(1, 1, 48, 20);
			Static_objects_[2]->StartPlayAnimation(1, 1, 22, 40);
			//end test code;------------------------------------------------------------------
		}
		return true;
	}
	return false;
}

bool BaseLevel::InputMouse(sf::Event::EventType event_type, sf::Vector2i mpuse_position) {
	return true;//////////////////////////////////////////////////////////////////////////////
}

void BaseLevel::InputEnemy() {
	//////////////////////////////////////////////////////////////////////////////////////////
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
	}
	// update animation and state for Players_objects_
	for (i = 0; i < (int)Players_objects_.size(); i++) {
		Players_objects_[i]->RecalculateState(game_timer);
		Players_objects_[i]->ForAnimation(game_timer);
	}
	// update animation and state for Shot_objects_
	for (i = 0; i < (int)Shot_objects_.size(); i++) {
		Shot_objects_[i]->RecalculateState(game_timer);
		Shot_objects_[i]->ForAnimation(game_timer);
	}
	// update animation for Ui_objects_
	for (i = 0; i < (int)Ui_objects_.size(); i++)
		Ui_objects_[i]->ForAnimation(game_timer);

	this->CalculateCollisionOnLevel();

	int j;
	for (i = 0; i < (int)Dies_objects_.size(); i++) {
		if (Dies_objects_[i]->GetTimeToRespawn() == 0) {
			Dies_objects_[i]->RestoreLife();
			Dies_objects_[i]->CollisionOn();
			j = 0;
			while (true) {
				Dies_objects_[i]->SetCoordinate(sf::Vector2f(float(rand() % size_level_width_),
															float(rand() % size_level_height_)));
				if (this->SafePointSpawn(Dies_objects_[i])) break;
				else {
					j++;
					if (j > 100) {
						Dies_objects_[i]->RestorePreviousState();
						break;
					}
				}
			}
			Dies_objects_.erase(Dies_objects_.begin() + i);
			Dies_objects_[i]->SafeState();
			i--;
		}
	}

	return true;
}

void BaseLevel::CalculateCollisionOnLevel() {
	bool recalc_i, recalc_all = true;
	int i, j;
	while (recalc_all) {
		recalc_all = false;

		//collisions for players
		for (i = 0; i < (int)Players_objects_.size(); i++) {
			recalc_i = false;
			for (j = 0; j < (int)Static_objects_.size(); j++) {
				if (Players_objects_[i]->SafeDistanceToCollision(Static_objects_[j],
					size_level_width_, size_level_height_, size_level_border_) < 0) {
					if (!Players_objects_[i]->Collision(Static_objects_[j],
							size_level_width_, size_level_height_, size_level_border_, true)) {
						j = -1;
						recalc_i = true;
						continue;
					}
				}
			}

			for (j = i + 1; j < (int)Players_objects_.size(); j++) {
				if (Players_objects_[i]->SafeDistanceToCollision(Players_objects_[j],
					size_level_width_, size_level_height_, size_level_border_) < 0) {
					if (!Players_objects_[i]->Collision(Players_objects_[j],
							size_level_width_, size_level_height_, size_level_border_, true)) {
						j = i;
						recalc_i = true;
						continue;
					}
				}
			}

			for (j = 0; j < (int)Enemy_objects_.size(); j++) {
				if (Players_objects_[i]->SafeDistanceToCollision(Enemy_objects_[j],
					size_level_width_, size_level_height_, size_level_border_) < 0) {
					if (!Players_objects_[i]->Collision(Enemy_objects_[j],
							size_level_width_, size_level_height_, size_level_border_, true)) {
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
		for (i = 0; i < (int)Enemy_objects_.size(); i++) {
			recalc_i = false;
			for (j = 0; j < (int)Static_objects_.size(); j++) {
				if (Enemy_objects_[i]->SafeDistanceToCollision(Static_objects_[j],
					size_level_width_, size_level_height_, size_level_border_) < 0) {
					if (!Enemy_objects_[i]->Collision(Static_objects_[j],
							size_level_width_, size_level_height_, size_level_border_, true)) {
						j = -1;
						recalc_i = true;
						continue;
					}
				}
			}

			for (j = 0; j < (int)Players_objects_.size(); j++) {
				if (Enemy_objects_[i]->SafeDistanceToCollision(Players_objects_[j],
					size_level_width_, size_level_height_, size_level_border_) < 0) {
					if (!Enemy_objects_[i]->Collision(Players_objects_[j],
							size_level_width_, size_level_height_, size_level_border_, true)) {
						j = -1;
						recalc_i = true;
						continue;
					}
				}
			}
			
			for (j = i + 1; j < (int)Enemy_objects_.size(); j++) {
				if (Enemy_objects_[i]->SafeDistanceToCollision(Enemy_objects_[j],
					size_level_width_, size_level_height_, size_level_border_) < 0) {
					if (!Enemy_objects_[i]->Collision(Enemy_objects_[j],
							size_level_width_, size_level_height_, size_level_border_, true)) {
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
	bool die_current_shot;
	for (i = 0; i < (int)Shot_objects_.size(); i++) {
		//check if shot is die
		if (Shot_objects_[i]->GetLifeLevel() != 0) {
			// shot is not die
			die_current_shot = false;
			for (j = 0; j < (int)Enemy_objects_.size(); j++) {				
				if (Shot_objects_[i]->GetPerrent() != Enemy_objects_[j] && //check if not parent
					Shot_objects_[i]->SafeDistanceToCollision(Enemy_objects_[j],
					size_level_width_, size_level_height_, size_level_border_) < 0) {
					if (!Shot_objects_[i]->Collision(Enemy_objects_[j],
						size_level_width_, size_level_height_, size_level_border_, false)) {
						//add Enemy_objects_[j] to vector Dies_objects_ and play dies
						die_current_shot = true;
						if (Enemy_objects_[j]->GetLifeLevel() != 0) {
							Enemy_objects_[j]->SetLifeLevel(-Shot_objects_[i]->GetLifeLevel(), 
																						true);
							if (Enemy_objects_[j]->GetLifeLevel() == 0) {
								Enemy_objects_[j]->SetDistanceMove(0);
								Enemy_objects_[j]->SetFreezeTime(5000);
								Enemy_objects_[j]->SetTimeToRespawn(5000);
								Dies_objects_.push_back(Enemy_objects_[j]);
							}
						}
					}
				}
			}

			for (j = 0; j < (int)Players_objects_.size(); j++) {
				if (Shot_objects_[i]->GetPerrent() != Players_objects_[j] && //check if not parent
					Shot_objects_[i]->SafeDistanceToCollision(Players_objects_[j],
					size_level_width_, size_level_height_, size_level_border_) < 0) {
					if (!Shot_objects_[i]->Collision(Players_objects_[j],
						size_level_width_, size_level_height_, size_level_border_, false)) {
						//add Players_objects_[j] to vector Dies_objects_ and play dies
						die_current_shot = true;
						if (Players_objects_[j]->GetLifeLevel() != 0) {
							Players_objects_[j]->SetLifeLevel(-Shot_objects_[i]->GetLifeLevel(), 
																						true);
							if (Players_objects_[j]->GetLifeLevel() == 0) {
								Players_objects_[j]->SetDistanceMove(0);
								Players_objects_[j]->SetFreezeTime(5000);
								Players_objects_[j]->SetTimeToRespawn(5000);
								Dies_objects_.push_back(Players_objects_[j]);
							}
						}
					}
				}
			}

			for (j = 0; j < (int)Static_objects_.size(); j++) {
				if (Shot_objects_[i]->GetPerrent() != Static_objects_[j] && //check if not parent
					Shot_objects_[i]->SafeDistanceToCollision(Static_objects_[j],
					size_level_width_, size_level_height_, size_level_border_) < 0) {
					if (!Shot_objects_[i]->Collision(Static_objects_[j],
						size_level_width_, size_level_height_, size_level_border_, false)) {
						//add Static_objects_[j] to vector Dies_objects_ and play dies
						die_current_shot = true;
						if (Static_objects_[j]->GetLifeLevel() != 0) {
							Static_objects_[j]->SetLifeLevel(-Shot_objects_[i]->GetLifeLevel(), 
																						true);
							if (Static_objects_[j]->GetLifeLevel() == 0) {
								Static_objects_[j]->SetTimeToRespawn(5000);
								Dies_objects_.push_back(Static_objects_[j]);
							}
						}
					}
				}
			}
			if (die_current_shot || Shot_objects_[i]->GetDistanceMove() == 0) {
				Shot_objects_[i]->SetDistanceMove(0);
				Shot_objects_[i]->SetLifeLevel(0);
			}
		}
		else {
			//shot is die
			if (Shot_objects_[i]->AnimationEnd()) {
				delete Shot_objects_[i];
				Shot_objects_.erase(Shot_objects_.begin() + i);
				i--;
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
			if (Static_objects_[i]->SafeDistanceToCollision(Game_object,
				size_level_width_, size_level_height_, size_level_border_) < cur_procent) 
				return false;
	}
	// check psition Game_object for Enemy_objects_
	cur_procent = level_size * min_distance_respawn_to_Enemy_objects_;
	for (i = 0; i < (int)Enemy_objects_.size(); i++) {
		if (Enemy_objects_[i] != Game_object)
			if (Enemy_objects_[i]->SafeDistanceToCollision(Game_object) < cur_procent) 
				return false;
	}

	// check psition Game_object for Players_objects_
	cur_procent = level_size * min_distance_respawn_to_Players_objects_;
	for (i = 0; i < (int)Players_objects_.size(); i++) {
		if (Players_objects_[i] != Game_object)
			if (Players_objects_[i]->SafeDistanceToCollision(Game_object) < cur_procent) 
				return false;
	}

	// check psition Game_object for Shot_objects_
	cur_procent = level_size * min_distance_respawn_to_Shot_objects_;
	for (i = 0; i < (int)Shot_objects_.size(); i++) {
		if (Shot_objects_[i]->SafeDistanceToCollision(Game_object) < cur_procent) 
			return false;
	}
	return true;
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

	for (i = 0; i < (int)Shot_objects_.size(); i++)		
		if (Shot_objects_.at(i)) delete Shot_objects_[i];
}
