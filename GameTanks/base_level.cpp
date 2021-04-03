#include "levels.h"

BaseLevel::BaseLevel() {
	size_level_width_ = SCREEN_RESOLUTION_X;
	size_level_height_ = SCREEN_RESOLUTION_Y;
}

sf::View& BaseLevel::Draw(sf::RenderWindow& window) {
	window.draw(Sprite_background_);
	for (auto const& object : Static_objects_)	object->Draw(window);
	if (Bonus_object_ != nullptr)				Bonus_object_->Draw(window);
	for (auto const& object : Enemy_objects_)	object->Draw(window);
	for (auto const& object : Players_objects_)	object->Draw(window);
	for (auto const& object : Shot_objects_)	object->Draw(window);
	window.draw(Sprite_border_);
	for (auto const& object : Ui_objects_)		object->Draw(window);
	CameraControl();
	return Player_camera_;
}

/*
	window.draw(Sprite_background_);
	int i;
	for (i = 0; i < (int)Static_objects_.size(); i++)	Static_objects_[i]->Draw(window);
	if (Bonus_object_ != nullptr)						Bonus_object_->Draw(window);
	for (i = 0; i < (int)Enemy_objects_.size(); i++)	Enemy_objects_[i]->Draw(window);
	for (i = 0; i < (int)Players_objects_.size(); i++)	Players_objects_[i]->Draw(window);
	for (auto const& item : Shot_objects_)				item->Draw(window);
	window.draw(Sprite_border_);
	for (i = 0; i < (int)Ui_objects_.size(); i++)		Ui_objects_[i]->Draw(window);
	CameraControl();
	return Player_camera_;
*/

bool BaseLevel::AddUiObject(UiObject* Ui_object) {
	if (Ui_object != nullptr) {
		Ui_objects_.push_back(Ui_object);
		Ui_object->SetCamera(&Player_camera_);
		Ui_object->SetIdObject(0);
		return true;
	}
	return false;
}

bool BaseLevel::AddStaticObject(GameObject* Static_objects,
		bool const& ignore_random_spawn) {
	if (Static_objects != nullptr 
			&& (ignore_random_spawn || this->RespawnObject(Static_objects))) {
		Static_objects->SafeState();
		Static_objects->SetGameType(STATIC);
		Static_objects_.push_back(Static_objects);
		All_objects_.push_back(Static_objects);
		if (Static_objects->GetSafeDistance() > max_safe_distance)
			max_safe_distance = Static_objects->GetSafeDistance();
		Static_objects->SetCamera(&Player_camera_);
		Static_objects->SetIdObject(count_id_objects_);
		count_id_objects_++;
		return true;
	}
	return false;
}

bool BaseLevel::AddEnemyObject(TankObject* Enemy_objects,
		bool const& ignore_random_spawn) {
	if (Enemy_objects != nullptr
			&& (ignore_random_spawn || this->RespawnObject(Enemy_objects))) {
		Enemy_objects->SafeState();
		Enemy_objects->SetGameType(ENEMY);
		Enemy_objects_.push_back(Enemy_objects);
		All_objects_.push_back(Enemy_objects);
		if (Enemy_objects->GetSafeDistance() > max_safe_distance)
			max_safe_distance = Enemy_objects->GetSafeDistance();
		Enemy_objects->SetCamera(&Player_camera_);
		Enemy_objects->SetIdObject(count_id_objects_);
		count_id_objects_++;
		enemy_shot_time_.push_back(0);
		return true;
	}
	return false;
}

bool BaseLevel::AddPlayerObject(TankObject* Player_objects,
		bool const& ignore_random_spawn) {
	if (Player_objects != nullptr
			&& (ignore_random_spawn || this->RespawnObject(Player_objects))) {
		Players_objects_.push_back(Player_objects);
		All_objects_.push_back(Player_objects);
		Player_objects->SetGameType(PLAYER); 
		if (Player_objects->GetSafeDistance() > max_safe_distance)
			max_safe_distance = Player_objects->GetSafeDistance();
		Player_objects->SetCamera(&Player_camera_);
		Player_objects->SetIdObject(count_id_objects_);
		count_id_objects_++;
		return true;
	}
	return false;
}

bool BaseLevel::AddShotObject(MovebleObject* Shot_objects) {
	if (Shot_objects != nullptr) {
		Shot_objects_.push_back(Shot_objects);
		All_objects_.push_back(Shot_objects);
		Shot_objects->SetGameType(SHOT);
		if (Shot_objects->GetSafeDistance() > max_safe_distance)
			max_safe_distance = Shot_objects->GetSafeDistance();
		Shot_objects->SetCamera(&Player_camera_);
		Shot_objects->SetIdObject(count_id_objects_);
		count_id_objects_++;
		return true;
	}
	return false;
}

bool BaseLevel::AddDieObject(GameObject* Dies_objects) {
	if (Dies_objects != nullptr
		&& Dies_objects->GetLifeLevel() == 0
		&& Dies_objects->GetTimeToRespawn() <= 0) {
		Dies_objects->SetTimeToRespawn(TIME_TO_RESPAWN);
		Dies_objects_.remove(Dies_objects);
		Dies_objects_.push_back(Dies_objects);
		return true;
	}
	Dies_objects = nullptr;
	return false;
}

bool BaseLevel::SetWatchObject(VisibleObject* Watch_object) { 
	if (Watch_object != nullptr) {
		Watch_object_ = Watch_object;
		return true;
	}
	return false;
}

bool BaseLevel::SetBonusObject(GameObject* Bonus_object) {
	if (Bonus_object != nullptr) {
		Bonus_object_ = Bonus_object;
		Bonus_object_->SetGameType(BONUS);
		Bonus_object_->SetIdObject(count_id_objects_);
		count_id_objects_++;
		return true;
	}
	return false;
}

TankObject* BaseLevel::GetPlayer(int const& player_number) {
	if (player_number >= 0 && player_number < (int)Players_objects_.size())
		return Players_objects_[player_number];
	return nullptr;
}

GameObject* BaseLevel::GetObjectById(int const& id_object) {
	for (auto item : All_objects_)
		if (item->GetIdObject() == id_object)
			return item;
	return nullptr;
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
	size_level_border_ = size_level_border;
}

void BaseLevel::SetBackgroundMusic(std::string music_address, float const& volume) {
	music_background_.openFromFile(music_address);
	music_background_.play();
	music_background_.setVolume(volume);
	music_background_.setLoop(true);
}

sf::Packet BaseLevel::GetPacketToSendAllClient(bool const& all_data) {
	sf::Packet Paket;
	if (Packet_send_.getDataSize() > 0) {
		Paket = Packet_send_;
		Packet_send_.clear();
	}
	return Paket;
}

void BaseLevel::RecvPacketFromServer(sf::Packet& Packet) {
	if (Packet.getDataSize() > 0) 
		Packets_recv_.push_back(Packet);
}

void BaseLevel::RecvPacketFromServerI(sf::Packet& Packet) {
	int id;
	std::string class_name = "";
	bool finded_id;
	int for_chect_error_packet = 0;
	while (!Packet.endOfPacket() && for_chect_error_packet < 100000) {
		for_chect_error_packet++;
		Packet >> id >> class_name;
		finded_id = false;
		for (auto item : All_objects_) {
			if (item->GetIdObject() == id) {
				finded_id = true;
				item->SetDataFromPacket(Packet);
				break;
			}
		}
		if (!finded_id) {
			GameObject* object = nullptr;
			if (class_name == "Bullet") object = new Bullet(0);
			else if (class_name == "DoubleBullet") object = new DoubleBullet(0);
			else if (class_name == "RedTank") object = new RedTank(0, 0, 0);
			else if (class_name == "TankBrown") object = new TankBrown(0, 0, 0);
			else if (class_name == "TankWhite") object = new TankWhite(0, 0, 0);
			else if (class_name == "TankBlack") object = new TankBlack(0, 0, 0);
			else if (class_name == "TankYellow") object = new TankYellow(0, 0, 0);
			else if (class_name == "TankGreen") object = new TankGreen(0, 0, 0);
			else if (class_name == "BarellBrown") object = new BarellBrown(0, 0, 0);
			else if (class_name == "BarellBroken") object = new BarellBroken(0, 0, 0);
			else if (class_name == "BarellGreen") object = new BarellGreen(0, 0, 0);
			else if (class_name == "BlockGround") object = new BlockGround(0, 0, 0);
			else if (class_name == "BlockGrass") object = new BlockGrass(0, 0, 0);
			else if (class_name == "CactusTypeOne") object = new CactusTypeOne(0, 0, 0);
			else if (class_name == "CactusTypeTwo") object = new CactusTypeTwo(0, 0, 0);
			else if (class_name == "CactusTypeThree") object = new CactusTypeThree(0,0,0);
			else if (class_name == "Log") object = new Log(0, 0, 0);
			else if (class_name == "Star") object = new Star(0, 0, 0);
			else if (class_name == "Stump") object = new Stump(0, 0, 0);
			else if (class_name == "TreeTypeOne") object = new TreeTypeOne(0, 0, 0);
			else if (class_name == "TreeTypeTwo") object = new TreeTypeTwo(0, 0, 0);
			else if (class_name == "TreeTypeThree") object = new TreeTypeThree(0, 0, 0);
			else if (class_name == "TreeTypeFour") object = new TreeTypeFour(0, 0, 0);
			else if (class_name == "TreeTypeFive") object = new TreeTypeFive(0, 0, 0);
			else if (class_name == "TreeTypeSix") object = new TreeTypeSix(0, 0, 0);
			else if (class_name == "TreeTypeSeven") object = new TreeTypeSeven(0, 0, 0);
			else if (class_name == "TreeTypeEight") object = new TreeTypeEight(0, 0, 0);
			else if (class_name == "TreeTypeNine") object = new TreeTypeNine(0, 0, 0);
			else if (class_name == "Well") object = new Well(0, 0, 0);
			
			if (object != nullptr) {
				object->SetDataFromPacket(Packet);
				if (object->GetGameType() == STATIC)
					this->AddStaticObject(object, true);
				else if (object->GetGameType() == ENEMY)
					this->AddEnemyObject((TankObject*)object, true);
				else if (object->GetGameType() == PLAYER)
					this->AddPlayerObject((TankObject*)object, true);
				else if (object->GetGameType() == SHOT)
					this->AddShotObject((MovebleObject*)object);
				else if (object->GetGameType() == BONUS)
					this->SetBonusObject(object);

				object->SetIdObject(id);
			}
		}
	}
}

int BaseLevel::AddPlayerFromLan() {

	TankObject* object = new RedTank(0, 200, 200);
	this->AddPlayerObject(object);
	return object->GetIdObject();
}

bool BaseLevel::InputKeyboard(int const& player_number, sf::Keyboard::Key Key) {
	if (player_number >= 0 && player_number < (int)Players_objects_.size()) {
		if (Key == sf::Keyboard::Up) Players_objects_[player_number]->MoveUp();
		if (Key == sf::Keyboard::Down) Players_objects_[player_number]->MoveDown();
		if (Key == sf::Keyboard::Left) Players_objects_[player_number]->MoveLeft();
		if (Key == sf::Keyboard::Right) Players_objects_[player_number]->MoveRight();
		if (Key == sf::Keyboard::Space)
			this->AddShotObject(Players_objects_[player_number]->CreateShot());
	}
	if (Focused_object != nullptr) {
		Focused_object->InputKey(Key);
	}
	return false;
}

bool BaseLevel::InputMouse(sf::Event::EventType event_type, 
	sf::Vector2i mouse_position) {
	sf::Vector2i coordinate_camera = 
		sf::Vector2i((int)Player_camera_.getCenter().x, (int)Player_camera_.getCenter().y)
		- sf::Vector2i((int)Player_camera_.getSize().x / 2,
			(int)Player_camera_.getSize().y / 2);
	bool result = false;
	if (event_type == sf::Event::EventType::MouseButtonReleased && 
			Focused_object != nullptr) {
		Focused_object->ShowCursorBlink(false);
		Focused_object = nullptr;
	}
	for (UiObject* ui : Ui_objects_) {
		result = ui->MouseInputToObject(event_type, mouse_position + coordinate_camera);
		if (event_type == sf::Event::EventType::MouseButtonReleased && result) {
			ui->ShowCursorBlink(true);
			if (ui->GetCursorBlink()) Focused_object = ui;
		}
	}
	return true;
}

void BaseLevel::InputEnemy() {
	for (int i = 0; i < (int)Enemy_objects_.size(); i++) {
		if (Enemy_objects_[i]->GetDistanceMove() <= 0 &&
			Enemy_objects_[i]->GetRotationDegree() == 0) { //for moving enemy
			if (rand() % 5 == 0) Enemy_objects_[i]->
					SetRotationDegree((rand() % ENEMY_ROTATION_DEGREE)
						- (float)ENEMY_ROTATION_DEGREE / 2);
			else Enemy_objects_[i]->
					SetDistanceMove(float(rand() % ENEMY_DISTANCE_MOVE) - 5);
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
		if (Static_objects_[i]->GetNeedSynchByLan() 
			&& (std::find(Need_sync_with_client_objects_.begin(),
				Need_sync_with_client_objects_.end(), 
				Static_objects_[i]) == Need_sync_with_client_objects_.end()))
			Need_sync_with_client_objects_.push_back(Static_objects_[i]);
	}
	// update animation and state for Bonus_object_
	if (Bonus_object_ != nullptr) 
		Bonus_object_->RecalculateState(game_timer);
	// update animation and state for Enemy_objects_
	for (i = 0; i < (int)Enemy_objects_.size(); i++) {
		Enemy_objects_[i]->RecalculateState(game_timer);
		enemy_shot_time_[i] -= game_timer;
		if (Enemy_objects_[i]->GetNeedSynchByLan()
			&& (std::find(Need_sync_with_client_objects_.begin(),
				Need_sync_with_client_objects_.end(),
				Enemy_objects_[i]) == Need_sync_with_client_objects_.end()))
			Need_sync_with_client_objects_.push_back(Enemy_objects_[i]);
	}
	// update animation and state for Players_objects_
	for (i = 0; i < (int)Players_objects_.size(); i++) {
		Players_objects_[i]->RecalculateState(game_timer);
		if (Players_objects_[i]->GetNeedSynchByLan()
			&& (std::find(Need_sync_with_client_objects_.begin(),
				Need_sync_with_client_objects_.end(),
				Players_objects_[i]) == Need_sync_with_client_objects_.end()))
			Need_sync_with_client_objects_.push_back(Players_objects_[i]);
	}
	for (MovebleObject* item : Shot_objects_) {
		item->RecalculateState(game_timer);
		if (item->GetNeedSynchByLan()
			&& (std::find(Need_sync_with_client_objects_.begin(),
				Need_sync_with_client_objects_.end(),
				item) == Need_sync_with_client_objects_.end()))
			Need_sync_with_client_objects_.push_back(item);
	}
	// update animation for Ui_objects_
	for (i = 0; i < (int)Ui_objects_.size(); i++)
		Ui_objects_[i]->RecalculateState(game_timer);


	for (GameObject* item : Dies_objects_) {
		if (item->GetTimeToRespawn() == 0) {
			item->RestoreLife();
			item->CollisionOn();
			if (this->RespawnObject(item)) {
				Dies_objects_.remove(item);
			}
		}
	}

	delete_item_need_sync_with_client_objects_ = true;
	for (MovebleObject* item : Shot_objects_) {
		if (item->GetLifeLevel() == 0
			&& item->AnimationEnd(true) && !item->PlaysSounds()) {
			if (!read_need_sync_with_client_objects_) {
				Shot_objects_.remove(item);
				All_objects_.remove(item);
				Need_sync_with_client_objects_.remove(item);
				delete item;
			}
		}
		else if (item->GetDistanceMove() <= 0)
			item->SetLifeLevel(0);
	}
	delete_item_need_sync_with_client_objects_ = false;


	sf::Packet Paket;
	for (auto item : All_objects_)
	{
		item->CreatePacket(Paket);
		item->SetNeedSynchByLan(false);
	}
	Packet_send_ = Paket;
	Paket.clear();

	while (!Packets_recv_.empty()) {
		this->RecvPacketFromServerI(Packets_recv_.front());
		//Packets_recv_.front().clear();
		//Packets_recv_.pop_front();
		Packets_recv_.clear();
	}

	return true;
}

bool compare(GameObject* first, GameObject* second)
{
	return (first->GetCoordinateCentre().x < second->GetCoordinateCentre().x);
}

void BaseLevel::CalculateCollisionOnLevel() {
	bool recalc_all = true;
	int i;
	while (recalc_all) {
		recalc_all = false;
		All_objects_.sort(compare);
		for (auto it = All_objects_.begin(); it != All_objects_.end(); ++it) {
			if ((*it)->GetGameType() == PLAYER &&
				!(*it)->Collision(Bonus_object_)) {
				((TankObject*)(*it))->AddBonus(new Bonuses());
				this->RespawnObject(Bonus_object_);
			}

			if ((*it)->GetGameType() == SHOT || (*it)->ObjectInRangeLevel(
				size_level_width_, size_level_height_, size_level_border_)) {
				auto it2(it); it2++;
				for (; it2 != All_objects_.end(); ++it2) {
					if ((((*it)->GetCoordinateCentre().x + max_safe_distance) >=
							((*it2)->GetCoordinateCentre().x - max_safe_distance))) {
						if ((*it)->SafeDistanceToCollision((*it2)) <= 0) {
							if (!(*it)->Collision((*it2))) {
								if		((*it)->GetGameType() == SHOT &&
										(*it2)->GetGameType() == SHOT) {
									if ((*it)->GetLifeLevel() != 0
											&& (*it2)->GetLifeLevel() != 0) {
										(*it)->SetLifeLevel(0);
										((MovebleObject*)(*it))->SetDistanceMove(0);
										(*it2)->SetLifeLevel(0);
										((MovebleObject*)(*it2))->SetDistanceMove(0);
									}
								}
								else if ((*it)->GetGameType() != SHOT &&
										(*it2)->GetGameType() != SHOT) {
									(*it)->RestorePreviousState();
									if ((*it)->GetGameType() != STATIC) {
										((MovebleObject*)(*it))->SetDistanceMove(0);
									}
									(*it2)->RestorePreviousState();
									if ((*it2)->GetGameType() != STATIC) {
										((MovebleObject*)(*it2))->SetDistanceMove(0);
									}
									(*it)->StartAudioAction("collision");
									(*it2)->StartAudioAction("collision");
									recalc_all = true;
								}
								else if ((*it)->GetGameType() == SHOT ||
										(*it2)->GetGameType() == SHOT) {
									GameObject* shot, * object;
									if ((*it)->GetGameType() == SHOT) {
										shot = (*it);
										object = (*it2);
									}
									else {
										shot = (*it2);
										object = (*it);
									}
									if (object->GetLifeLevel() != 0) {
										if (object->GetGameType() == STATIC)
											object->StartAudioAction("collision");
										//add current point:
										if (shot->GetPerrent() != nullptr) {
											float procent = 
												(float)shot->GetLifeLevel() /
												(float)object->GetMaxLifeLevel();
											if (procent > 1) procent = 1.0f;
											shot->GetPerrent()->SetCurrentPoint(
												int(object->GetBasePoint() * procent));

											int temp = (int)(object->GetCurrentPoint()
												* procent * TRANSFER_PERCENTAGE_POINT);

											shot->GetPerrent()->SetCurrentPoint(temp);
											object->SetCurrentPoint(-temp);
										}
										//work by shooting:
										object->SetLifeLevel(
											-shot->GetLifeLevel(), true);
										this->AddDieObject((MovebleObject*)object);
									}
									shot->SetLifeLevel(0);
									((MovebleObject*)shot)->SetDistanceMove(0);
								}
							}
						}
					}
					else break;
				}
			}
			else {
				if ((*it)->GetGameType() != STATIC) {
					(*it)->RestorePreviousState();
					((MovebleObject*)(*it))->SetDistanceMove(0);
					(*it)->StartAudioAction("collision");
					recalc_all = true;
				}
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
		Game_object->SetRotation(float(rand() % 360));
		if (this->SafePointSpawn(Game_object)) {
			return true;
		}
	}
	std::cout << "error respawn: 100000;" << std::endl;
	Game_object->RestorePreviousState();
	Game_object = nullptr;
	return false;
}

bool BaseLevel::ExitLevel(sf::Packet& Result_level) {
	return false;
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
