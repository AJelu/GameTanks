#include "Levels.h"

GameLevel::GameLevel() : BaseLevel() {
	/* Initialization tile map and border: */
	this->SetBackgroundTexture("Data/Maps/Map.png");
	this->SetBorderTexture("Data/Maps/Map_border.png", 50);
	this->SetBackgroundMusic("Data/Audio/music/music_in_game.ogg", 10);

	/* Respawn player: */
	this->Player_ = new TankBrown(1, 200, 200);
	this->AddPlayerObject(Player_);
	this->SetWatchObject(Player_);

	/* Respawn test bonus: */
	this->SetBonusObject(new TankBlack(1, 500, 500));

	/* Respawn enemy: */
	TankObject* tank_enemy = nullptr;
	for (int i = 0; i < 50; i++) this->AddEnemyObject(tank_enemy = new RedTank(1, 300, 400));
	
	/* Respawn static objects: */
	BarellBrown* static_barell_brown = nullptr;
	this->SpawnObject(static_barell_brown, 60, 1, 200, 200);

	BarellBroken* static_barell_broken = nullptr;
	this->SpawnObject(static_barell_broken, 60, 1, 200, 200);

	BarellGreen* static_barell_green = nullptr;
	this->SpawnObject(static_barell_green, 60, 1, 200, 200);

	BlockGround* static_block_ground = nullptr;
	this->SpawnObject(static_block_ground, 50, 1, 200, 200);

	BlockGrass* static_block_grass = nullptr;
	this->SpawnObject(static_block_grass, 50, 1, 200, 200);

	CactusTypeOne* static_cactus_type_one = nullptr;
	this->SpawnObject(static_cactus_type_one, 40, 1, 200, 200);

	CactusTypeTwo* static_cactus_type_two = nullptr;
	this->SpawnObject(static_cactus_type_two, 40, 1, 200, 200);

	CactusTypeThree* static_cactus_type_three = nullptr;
	this->SpawnObject(static_cactus_type_three, 40, 1, 200, 200);

	Log* static_log = nullptr;
	this->SpawnObject(static_log, 50, 1, 200, 200);

	Stump* static_stump = nullptr;
	this->SpawnObject(static_stump, 40, 1, 200, 200);

	TreeTypeOne* static_tree_type_one = nullptr;
	this->SpawnObject(static_tree_type_one, 90, 1, 200, 200);

	TreeTypeTwo* static_tree_type_two = nullptr;
	this->SpawnObject(static_tree_type_two, 90, 1, 200, 200);

	TreeTypeThree* static_tree_type_three = nullptr;
	this->SpawnObject(static_tree_type_three, 90, 1, 200, 200);

	TreeTypeFour* static_tree_type_four = nullptr;
	this->SpawnObject(static_tree_type_four, 90, 1, 200, 200);

	TreeTypeFive* static_tree_type_five = nullptr;
	this->SpawnObject(static_tree_type_five, 90, 1, 200, 200);

	TreeTypeSix* static_tree_type_six = nullptr;
	this->SpawnObject(static_tree_type_six, 90, 1, 200, 200);

	TreeTypeSeven* static_tree_type_seven = nullptr;
	this->SpawnObject(static_tree_type_seven, 40, 1, 200, 200);

	TreeTypeEight* static_tree_type_eight = nullptr;
	this->SpawnObject(static_tree_type_eight, 40, 1, 200, 200);

	TreeTypeNine* static_tree_type_nine = nullptr;
	this->SpawnObject(static_tree_type_nine, 40, 1, 200, 200);

	Well* static_well = nullptr;
	this->SpawnObject(static_well, 40, 1, 200, 200);
	/*------------------------------*/

	float a = 20, m = 3;
	Point_current_		= new Button(sf::Vector2f(a, a + a * m * 0), sf::Vector2f(0, 0));
	Life_				= new Button(sf::Vector2f(a, a + a * m * 1), sf::Vector2f(0, 0));
	Speed_				= new Button(sf::Vector2f(a, a + a * m * 2), sf::Vector2f(0, 0));
	Rotation_speed_		= new Button(sf::Vector2f(a, a + a * m * 3), sf::Vector2f(0, 0));
	Speed_shot_			= new Button(sf::Vector2f(a, a + a * m * 4), sf::Vector2f(0, 0));
	Shot_distance_		= new Button(sf::Vector2f(a, a + a * m * 5), sf::Vector2f(0, 0));
	Time_to_next_shot_	= new Button(sf::Vector2f(a, a + a * m * 6), sf::Vector2f(0, 0));
	Shot_life_			= new Button(sf::Vector2f(a, a + a * m * 7), sf::Vector2f(0, 0));

	sf::Vector2f scale = sf::Vector2f(0.5f, 0.3f);
	Point_current_->SetScale(scale);
	Life_->SetScale(scale);
	Speed_->SetScale(scale);
	Rotation_speed_->SetScale(scale);
	Speed_shot_->SetScale(scale);
	Shot_distance_->SetScale(scale);
	Time_to_next_shot_->SetScale(scale);
	Shot_life_->SetScale(scale);

	int text_size = 20;
	Point_current_->SetCharacterSize(text_size);
	Life_->SetCharacterSize(text_size);
	Speed_->SetCharacterSize(text_size);
	Rotation_speed_->SetCharacterSize(text_size);
	Speed_shot_->SetCharacterSize(text_size);
	Shot_distance_->SetCharacterSize(text_size);
	Time_to_next_shot_->SetCharacterSize(text_size);
	Shot_life_->SetCharacterSize(text_size);

	float text_align = -0.01f;
	Point_current_->SetTextAlign(text_align);
	Life_->SetTextAlign(text_align);
	Speed_->SetTextAlign(text_align);
	Rotation_speed_->SetTextAlign(text_align);
	Speed_shot_->SetTextAlign(text_align);
	Shot_distance_->SetTextAlign(text_align);
	Time_to_next_shot_->SetTextAlign(text_align);
	Shot_life_->SetTextAlign(text_align);

	this->AddUiObject(Point_current_);
	this->AddUiObject(Life_);
	this->AddUiObject(Speed_);
	this->AddUiObject(Rotation_speed_);
	this->AddUiObject(Speed_shot_);
	this->AddUiObject(Shot_distance_);
	this->AddUiObject(Time_to_next_shot_);
	this->AddUiObject(Shot_life_);
}

template <class TypeObject>
void GameLevel::SpawnObject(TypeObject* object, int const& quantity,
	int const& id_object, float const& spawn_x, float const& spawn_y) {

	for (int i = 0; i < quantity; i++)
		this->AddStaticObject(object = new TypeObject(id_object, spawn_x, spawn_y));
}

bool GameLevel::UpdateState(float& game_timer) {
	bool result = BaseLevel::UpdateState(game_timer);
	std::stringstream stream;
	stream << "Points: " << Player_->GetCurrentPoint();
	Point_current_->SetText(stream.str());
	stream.str("");

	stream << "Life: " << Player_->GetLifeLevel() << "\\" << Player_->GetMaxLifeLevel();
	Life_->SetText(stream.str());
	stream.str("");

	if (Player_->GetBonus() != nullptr) {
		stream << "Speed: " << Player_->GetBonus()->GetOriginalSpeedMove();
		stream << "(" << Player_->GetBonus()->GetSpeedMove() << ")";
	}
	else stream << "Speed: " << Player_->GetSpeedMove();
	Speed_->SetText(stream.str());
	stream.str("");

	if (Player_->GetBonus() != nullptr) {
		stream << "Rotation speed: " << Player_->GetBonus()->GetOriginalRotationSpeed();
		stream << "(" << Player_->GetBonus()->GetRotationSpeed() << ")";
	}
	else stream << "Rotation speed: " << Player_->GetRotationSpeed();
	Rotation_speed_->SetText(stream.str());
	stream.str("");

	if (Player_->GetBonus() != nullptr) {
		stream << "Speed shot: " << Player_->GetBonus()->GetOriginalSpeedShot();
		stream << "(" << Player_->GetBonus()->GetSpeedShot() << ")";
	}
	else stream << "Speed shot: " << Player_->GetSpeedShot();
	Speed_shot_->SetText(stream.str());
	stream.str("");

	if (Player_->GetBonus() != nullptr) {
		stream << "Shot distance: " << Player_->GetBonus()->GetOriginalShotDistance();
		stream << "(" << Player_->GetBonus()->GetShotDistance() << ")";
	}
	else stream << "Shot distance: " << Player_->GetShotDistance();
	Shot_distance_->SetText(stream.str());
	stream.str("");

	if (Player_->GetBonus() != nullptr) {
		stream << "Time shot: " << Player_->GetBonus()->GetOriginalTimeFreezeShot();
		stream << "(" << Player_->GetBonus()->GetTimeFreezeShot() << ")";
	}
	else stream << "Time shot: " << Player_->GetTimeFreezeShot();
	Time_to_next_shot_->SetText(stream.str());
	stream.str("");

	if (Player_->GetBonus() != nullptr) {
		stream << "Shot life: " << Player_->GetBonus()->GetOriginalShotLife();
		stream << "(" << Player_->GetBonus()->GetShotLife() << ")";
	}
	else stream << "Shot life: " << Player_->GetLifeShot();
	Shot_life_->SetText(stream.str());
	stream.str("");

	return result;
}

int GameLevel::NextLevel() {
	bool result = BaseLevel::NextLevel();
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	return result;
}

bool GameLevel::ExitGame() {
	bool result = BaseLevel::ExitGame();
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	return result;
}
