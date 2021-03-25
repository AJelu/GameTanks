#include "ready_objects.h"

CommonGameObject::CommonGameObject(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	std::string const& texture, int const& frame_count_x, int const& frame_count_y,
	int const& max_life_level)
	: GameObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y, max_life_level){}

void CommonGameObject::ActionDie() {

}

void CommonGameObject::ActionLife() {

}

BarellBrown::BarellBrown(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Barell_01.png",			//texture
		1, 1,									//frame count
		1) {									//max life level
	
	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

BarellBroken::BarellBroken(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Barell_02.png",			//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

BarellGreen::BarellGreen(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Barell_03.png",			//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

BlockGround::BlockGround(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(64, 64),					//offset
		"Data/Static/Block_01.png",				//texture
		1, 1,									//frame count
		3) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(1, 1));
}

BlockGrass::BlockGrass(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(64, 64),					//offset
		"Data/Static/Block_02.png",				//texture
		1, 1,									//frame count
		3) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(1, 1));
}

CactusTypeOne::CactusTypeOne(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Cactus_01.png",			//texture
		1, 1,									//frame count
		3) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

CactusTypeTwo::CactusTypeTwo(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Cactus_02.png",			//texture
		1, 1,									//frame count
		3) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

CactusTypeThree::CactusTypeThree(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Cactus_03.png",			//texture
		1, 1,									//frame count
		3) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

Log::Log(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Cactus_03.png",			//texture
		1, 1,									//frame count
		3) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

Star::Star(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Star.png",					//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

Stump::Stump(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Stump.png",				//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

TreeTypeOne::TreeTypeOne(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_01.png",				//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

TreeTypeTwo::TreeTypeTwo(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_02.png",				//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

TreeTypeThree::TreeTypeThree(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_03.png",				//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

TreeTypeFour::TreeTypeFour(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_04.png",				//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

TreeTypeFive::TreeTypeFive(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_05.png",				//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

TreeTypeSix::TreeTypeSix(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_06.png",				//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

TreeTypeSeven::TreeTypeSeven(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_07.png",				//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

TreeTypeEight::TreeTypeEight(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_08.png",				//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

TreeTypeNine::TreeTypeNine(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Tree_09.png",				//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}

Well::Well(int const& id_object, float const& spawn_x, float const& spawn_y)
	: CommonGameObject(
		id_object,
		sf::Vector2f(spawn_x, spawn_y),			//coordinate centr
		sf::Vector2f(128, 128),					//offset
		"Data/Static/Well.png",					//texture
		1, 1,									//frame count
		1) {									//max life level

	this->AddCollision(new RoundCollision(sf::Vector2f(0, 0), 10));
	this->SetScale(sf::Vector2f(0.5, 0.5));
}