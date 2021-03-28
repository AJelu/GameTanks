#include "ready_objects.h"

CommonGameObject::CommonGameObject(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	std::string const& texture,
	int const& max_life_level)
	: GameObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, 12, 3, max_life_level){
}

void CommonGameObject::ActionDie() {
	this->StartAudioAction("destructible");
	this->StartPlayAnimation(2, 1, 12, 20);
}

void CommonGameObject::ActionLife() {
	this->StartPlayAnimation(1, 12, 1, 20);
}

void CommonGameObject::ActionChangeLifeLevel(int const& life_level) {
	int frame = 12 - int((((float)life_level) / (float)this->GetMaxLifeLevel()) * 11.0f) + 1;
	this->StartPlayAnimation(3, frame, frame, 20);
}

BarellBrown::BarellBrown(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Barell_01.png",			//texture
		1) {									//max life level
	
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 8));
	this->SetScale(sf::Vector2f(0.3f, 0.3f));
}

std::string BarellBrown::ClassName() { return "BarellBrown"; }

BarellBroken::BarellBroken(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Barell_02.png",			//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 8));
	this->SetScale(sf::Vector2f(0.3f, 0.3f));
}

std::string BarellBroken::ClassName() { return "BarellBroken"; }

BarellGreen::BarellGreen(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Barell_03.png",			//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 8));
	this->SetScale(sf::Vector2f(0.3f, 0.3f));
}

std::string BarellGreen::ClassName() { return "BarellGreen"; }

BlockGround::BlockGround(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(64, 64),					//offset
		"Data/Static/Block_01.png",				//texture
		3) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 40));
	this->SetScale(sf::Vector2f(1.f, 1.f));
	this->AddAudioAction("destructible", "Data/Audio/destructible/destructible_big.ogg");
}

std::string BlockGround::ClassName() { return "BlockGround"; }

BlockGrass::BlockGrass(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(64, 64),					//offset
		"Data/Static/Block_02.png",				//texture
		3) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 40));
	this->SetScale(sf::Vector2f(1, 1));
	this->AddAudioAction("destructible", "Data/Audio/destructible/destructible_big.ogg");
}

std::string BlockGrass::ClassName() { return "BlockGrass"; }

CactusTypeOne::CactusTypeOne(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Cactus_01.png",			//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/damage_tree.ogg");
}

std::string CactusTypeOne::ClassName() { return "CactusTypeOne"; }

CactusTypeTwo::CactusTypeTwo(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Cactus_02.png",			//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/damage_tree.ogg");
}

std::string CactusTypeTwo::ClassName() { return "CactusTypeTwo"; }

CactusTypeThree::CactusTypeThree(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Cactus_03.png",			//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/damage_tree.ogg");
}

std::string CactusTypeThree::ClassName() { return "CactusTypeThree"; }

Log::Log(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Cactus_03.png",			//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

std::string Log::ClassName() { return "Log"; }

Star::Star(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Star.png",					//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/star_up.ogg");
	ActionLife();
}

void Star::ActionLife() {
	CommonGameObject::ActionLife();
	this->StartPlayAnimation(3, 12, 1, 80, true);
}

std::string Star::ClassName() { return "Star"; }

Stump::Stump(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Stump.png",				//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

std::string Stump::ClassName() { return "Stump"; }

TreeTypeOne::TreeTypeOne(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_01.png",				//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/damage_tree.ogg");
}

std::string TreeTypeOne::ClassName() { return "TreeTypeOne"; }

TreeTypeTwo::TreeTypeTwo(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_02.png",				//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/damage_tree.ogg");
}

std::string TreeTypeTwo::ClassName() { return "TreeTypeTwo"; }

TreeTypeThree::TreeTypeThree(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_03.png",				//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/damage_tree.ogg");
}

std::string TreeTypeThree::ClassName() { return "TreeTypeThree"; }

TreeTypeFour::TreeTypeFour(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_04.png",				//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/damage_tree.ogg");
}

std::string TreeTypeFour::ClassName() { return "TreeTypeFour"; }

TreeTypeFive::TreeTypeFive(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_05.png",				//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/damage_tree.ogg");
}

std::string TreeTypeFive::ClassName() { return "TreeTypeFive"; }

TreeTypeSix::TreeTypeSix(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_06.png",				//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/damage_tree.ogg");
}

std::string TreeTypeSix::ClassName() { return "TreeTypeSix"; }

TreeTypeSeven::TreeTypeSeven(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_07.png",				//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/damage_tree.ogg");
}

std::string TreeTypeSeven::ClassName() { return "TreeTypeSeven"; }

TreeTypeEight::TreeTypeEight(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_08.png",				//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/damage_tree.ogg");
}

std::string TreeTypeEight::ClassName() { return "TreeTypeEight"; }

TreeTypeNine::TreeTypeNine(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_09.png",				//texture
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/damage_tree.ogg");
}

std::string TreeTypeNine::ClassName() { return "TreeTypeNine"; }

Well::Well(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Well.png",					//texture
		2) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
	this->AddAudioAction("destructible", "Data/Audio/destructible/destructible_small.ogg");
}

std::string Well::ClassName() { return "Well"; }
