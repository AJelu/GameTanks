#include "Levels.h"

GameLevel::GameLevel(int const& id_watch_object) : BaseLevel() {
	/* Initialization tile map and border: */
	this->SetBackgroundTexture("Data/Maps/Map.png");
	this->SetBorderTexture("Data/Maps/Map_border.png", 50);
	this->SetBackgroundMusic("Data/Audio/music/music_in_game.ogg", 10);
	
	Player_ = nullptr;
	if (id_watch_object == 0) {
		switch (rand() % 6) {
			case 0:	Player_ = new RedTank(1, 0, 0);
				break;
			case 1:	Player_ = new TankBrown(1, 0, 0);
				break;
			case 2:	Player_ = new TankWhite(1, 0, 0);
				break;
			case 3:	Player_ = new TankBlack(1, 0, 0);
				break;
			case 4:	Player_ = new TankYellow(1, 0, 0);
				break;
			case 5:	Player_ = new TankGreen(1, 0, 0);
				break;
			default: Player_ = new TankYellow(1, 0, 0);
				break;
		}
		this->AddPlayerObject(Player_);
		this->SetWatchObject(Player_);
		player_id_ = Player_->GetIdObject();


		/* Respawn test bonus: */
		this->SetBonusObject(new Star(1, 0, 0));


		/* Respawn enemy: */
		RedTank* red_tank_enemy = nullptr;
		this->SpawnEnemyObject(red_tank_enemy, 10, 1, 300, 400);

		TankBrown* brown_tank_enemy = nullptr;
		this->SpawnEnemyObject(brown_tank_enemy, 10, 1, 300, 400);

		TankWhite* white_tank_enemy = nullptr;
		this->SpawnEnemyObject(white_tank_enemy, 10, 1, 300, 400);

		TankBlack* black_tank_enemy = nullptr;
		this->SpawnEnemyObject(black_tank_enemy, 10, 1, 300, 400);

		TankYellow* yellow_tank_enemy = nullptr;
		this->SpawnEnemyObject(yellow_tank_enemy, 10, 1, 300, 400);

		TankGreen* green_tank_enemy = nullptr;
		this->SpawnEnemyObject(green_tank_enemy, 10, 1, 300, 400);


		/* Respawn static objects: */
		BarellBrown* static_barell_brown = nullptr;
		this->SpawnStaticObject(static_barell_brown, 60, 1, 200, 200);

		BarellBroken* static_barell_broken = nullptr;
		this->SpawnStaticObject(static_barell_broken, 60, 1, 200, 200);

		BarellGreen* static_barell_green = nullptr;
		this->SpawnStaticObject(static_barell_green, 60, 1, 200, 200);

		BlockGround* static_block_ground = nullptr;
		this->SpawnStaticObject(static_block_ground, 50, 1, 200, 200);

		BlockGrass* static_block_grass = nullptr;
		this->SpawnStaticObject(static_block_grass, 50, 1, 200, 200);

		CactusTypeOne* static_cactus_type_one = nullptr;
		this->SpawnStaticObject(static_cactus_type_one, 20, 1, 200, 200);

		CactusTypeTwo* static_cactus_type_two = nullptr;
		this->SpawnStaticObject(static_cactus_type_two, 30, 1, 200, 200);

		CactusTypeThree* static_cactus_type_three = nullptr;
		this->SpawnStaticObject(static_cactus_type_three, 30, 1, 200, 200);

		Log* static_log = nullptr;
		this->SpawnStaticObject(static_log, 50, 1, 200, 200);

		Stump* static_stump = nullptr;
		this->SpawnStaticObject(static_stump, 40, 1, 200, 200);

		TreeTypeOne* static_tree_type_one = nullptr;
		this->SpawnStaticObject(static_tree_type_one, 80, 1, 200, 200);

		TreeTypeTwo* static_tree_type_two = nullptr;
		this->SpawnStaticObject(static_tree_type_two, 80, 1, 200, 200);

		TreeTypeThree* static_tree_type_three = nullptr;
		this->SpawnStaticObject(static_tree_type_three, 80, 1, 200, 200);

		TreeTypeFour* static_tree_type_four = nullptr;
		this->SpawnStaticObject(static_tree_type_four, 80, 1, 200, 200);

		TreeTypeFive* static_tree_type_five = nullptr;
		this->SpawnStaticObject(static_tree_type_five, 80, 1, 200, 200);

		TreeTypeSix* static_tree_type_six = nullptr;
		this->SpawnStaticObject(static_tree_type_six, 80, 1, 200, 200);

		TreeTypeSeven* static_tree_type_seven = nullptr;
		this->SpawnStaticObject(static_tree_type_seven, 30, 1, 200, 200);

		TreeTypeEight* static_tree_type_eight = nullptr;
		this->SpawnStaticObject(static_tree_type_eight, 30, 1, 200, 200);

		TreeTypeNine* static_tree_type_nine = nullptr;
		this->SpawnStaticObject(static_tree_type_nine, 30, 1, 200, 200);

		Well* static_well = nullptr;
		this->SpawnStaticObject(static_well, 30, 1, 200, 200);
		/*------------------------------*/
	}
	else player_id_ = id_watch_object;

	Stats_ = new TextLine(sf::Vector2f(20, 20), 250, 8, 21, 40, 43);
	Stats_->SetStartCoorditateTop();
	Stats_->SetStartCoorditateLeft();
	Stats_->TextAlign(0);
	this->AddUiObject(Stats_);	

	Exit_ = new Button(sf::Vector2f(20, 20), sf::Vector2f(0, 0));
	Exit_->SetScale(sf::Vector2f(0.25f, 0.2f));
	Exit_->SetOffsetSprite(sf::Vector2f((float)Exit_->GetWidthSprite(), 
		(float)Exit_->GetHeightSprite()));
	Exit_->SetCharacterSize(30);
	Exit_->SetTextAlign(0);
	Exit_->SetText("EXIT");
	Exit_->SetStartCoorditateRight();
	Exit_->SetStartCoorditateBottom();
	this->AddUiObject(Exit_);

	Point_board = new TextLine(sf::Vector2f(220, 20), 200, 5, 25, 30, 33);
	Point_board->SetStartCoorditateTop();
	Point_board->SetStartCoorditateRight();
	Point_board->TextAlign(0);
	this->AddUiObject(Point_board);

	Progress_life_ = new ProgressLine(sf::Vector2f(20, 50));
	Progress_life_->SetScale(sf::Vector2f(250.f, 40.f));
	Progress_life_->SetStartCoorditateLeft();
	Progress_life_->SetStartCoorditateBottom();
	Progress_life_->SetTextAlign(0.f);
	Progress_life_->SetCharacterSize(18);
	this->AddUiObject(Progress_life_);

	Progress_Shot_ = new ProgressLine(sf::Vector2f(20, 100));
	Progress_Shot_->SetScale(sf::Vector2f(250.f, 40.f));
	Progress_Shot_->SetStartCoorditateLeft();
	Progress_Shot_->SetStartCoorditateBottom();
	Progress_Shot_->SetTextAlign(0.f);
	Progress_Shot_->SetCharacterSize(18);
	Progress_Shot_->SetText("Shot");
	this->AddUiObject(Progress_Shot_);
}

template <class TypeObject>
void GameLevel::SpawnStaticObject(TypeObject* object, int const& quantity,
	int const& id_object, float const& spawn_x, float const& spawn_y) {

	for (int i = 0; i < quantity; i++)
		this->AddStaticObject(object = new TypeObject(id_object, spawn_x, spawn_y));
}

template <class TypeObject>
void GameLevel::SpawnEnemyObject(TypeObject* object, int const& quantity,
	int const& id_object, float const& spawn_x, float const& spawn_y) {

	for (int i = 0; i < quantity; i++)
		this->AddEnemyObject(object = new TypeObject(id_object, spawn_x, spawn_y));
}

bool GameLevel::UpdateState(float& game_timer) {
	bool result = BaseLevel::UpdateState(game_timer);

	//if client and not recev object for game and watch
	if (Player_ == nullptr) {
		GameObject* temp_ptr = this->GetObjectById(player_id_);
		if (temp_ptr == nullptr || temp_ptr->GetGameType() != PLAYER)
			return result;
		Player_ = (TankObject*)temp_ptr;
		this->SetWatchObject(Player_);
	}


	//other manipulation on game level:
	Progress_life_->SetProgress(Player_->GetLifeLevel() / 
		float(Player_->GetMaxLifeLevel()));
	Progress_life_->SetText("LIFE");
	Progress_Shot_->SetProgress(1.f - Player_->GetTimeToNextShot() /
		(Player_->GetTimeFreezeShot()));

	StatsOutput("SCORE POINT: ", Player_->GetCurrentPoint(), 0, Player_);
	StatsOutput("HIT POINT: ", Player_->GetLifeLevel(), 1, Player_, 
		float(Player_->GetMaxLifeLevel()));
	if (Player_->GetBonus() != nullptr) {
		StatsOutput("DAMAGE: ", Player_->GetLifeShot(), 2, Player_,
			float(Player_->GetBonus()->GetOriginalShotLife()), 
			float(Player_->GetBonus()->GetShotLife()));
		StatsOutput("ATTACK RANGE: ", Player_->GetShotDistance(), 3, Player_,
			Player_->GetBonus()->GetOriginalShotDistance(), 
			Player_->GetBonus()->GetShotDistance());
		StatsOutput("ATTACK SPEED: ", Player_->GetSpeedShot(), 4, Player_,
			Player_->GetBonus()->GetOriginalSpeedShot(), 
			Player_->GetBonus()->GetSpeedShot());
		StatsOutput("RECHARGE: ", Player_->GetTimeFreezeShot(), 5, Player_,
			Player_->GetBonus()->GetOriginalTimeFreezeShot(), 
			Player_->GetBonus()->GetTimeFreezeShot());
		StatsOutput("MOBILITY: ", Player_->GetRotationSpeed(), 6, Player_,
			Player_->GetBonus()->GetOriginalRotationSpeed(), 
			Player_->GetBonus()->GetRotationSpeed());
		StatsOutput("SPEED: ", Player_->GetSpeedMove(), 7, Player_,
			Player_->GetBonus()->GetOriginalSpeedMove(), 
			Player_->GetBonus()->GetSpeedMove());
	}
	else {
		StatsOutput("DAMAGE: ", Player_->GetLifeShot(), 2, Player_);
		StatsOutput("ATTACK RANGE: ", Player_->GetShotDistance(), 3, Player_);
		StatsOutput("ATTACK SPEED: ", Player_->GetSpeedShot(), 4, Player_);
		StatsOutput("RECHARGE: ", Player_->GetTimeFreezeShot(), 5, Player_);
		StatsOutput("MOBILITY: ", Player_->GetRotationSpeed(), 6, Player_);
		StatsOutput("SPEED: ", Player_->GetSpeedMove(), 7, Player_);
	}

	Progress_life_->SetText(Stats_->GetTextLine(1));

	return result;
}

template <class TypeStatValue>
void GameLevel::StatsOutput(std::string stat_name, TypeStatValue const& stat_base_value,
	int const& stat_object, TankObject* player_object,
	float const& initial_base_value, float const& stat_bonus_value) {

	std::stringstream stream;
	if (stat_name == "SCORE POINT: ") stream << stat_name << stat_base_value;
	else  if (stat_name == "HIT POINT: ")
		stream << stat_name << stat_base_value << " \\" << int(initial_base_value);
	else if (player_object->GetBonus() != nullptr)
		stream << stat_name << initial_base_value << " > " << int(stat_bonus_value);
	else stream << stat_name  << stat_base_value;
	Stats_->SetTextLine(stream.str(), stat_object);
	stream.str("");
}

bool GameLevel::ExitLevel(sf::Packet& Result_level) {
	bool result = BaseLevel::ExitLevel(Result_level);
	if (Exit_->GetMouseUpOnThis(true)) {
		Result_level << Level_type::MENU_LEVEL;
		Result_level << "";
		return true;
	}
	return result;
}