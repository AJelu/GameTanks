#include "levels.h"

BaseLevel::BaseLevel()
{
	/* Initialization tile map: */
	Texture_background_.loadFromFile("Data/Map.png");
	Sprite_background_.setTexture(Texture_background_);
	Sprite_background_.setPosition(0, 0);


	this->AddPlayerObject(new RedTank(1, 200, 200));

	this->AddEnemyObject(new RedTank(1, 300, 400));
	this->AddEnemyObject(new RedTank(1, 600, 400));
	this->AddEnemyObject(new RedTank(1, 600, 600));


	/* temporarily for the test */
	animation = VisibleObject(2,
		sf::Vector2f(270, 270), sf::Vector2f(165, 189),
		"Data/BoomTest2.png", 
		36, 1);
	/* temporarily for the test */


	/* Initialization border map: */
	Texture_border_.loadFromFile("Data/Map_border.png");
	Sprite_border_.setTexture(Texture_border_);
	Sprite_border_.setPosition(0, 0);
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
	
	Player_client.Draw(window, nullptr);
	Player_camera.setCenter(Players_objects_[0]->GetCoordinateCentre().x,
							Players_objects_[0]->GetCoordinateCentre().y);

	animation.Draw(window, nullptr); /* temporarily for the test */

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

BaseObject* BaseLevel::GetObjectToSendClient()
{
	return nullptr;
}

void BaseLevel::RecvObjectFromServer()
{
}

bool BaseLevel::InputKeyboard(bool for_client, sf::Keyboard::Key Key)
{
	if (Key == Keyboard::Up) {
		Players_objects_[0]->MoveUp();
	}
	if (Key == Keyboard::Down) {
		Players_objects_[0]->MoveDown();
	}
	if (Key == Keyboard::Left) {
		Players_objects_[0]->MoveLeft();
	}
	if (Key == Keyboard::Right) {
		Players_objects_[0]->MoveRight();
	}
	if (Key == Keyboard::Space) {
		this->AddShotObject(Players_objects_[0]->CreateShot());
	}
	return true;
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
						j = -1;
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
				//cout << Enemy_objects_[i]->SafeDistanceToCollision(Players_objects_[j]) << endl;
				if (Enemy_objects_[i]->SafeDistanceToCollision(Players_objects_[j]) < 0) {
					if (!Enemy_objects_[i]->Collision(Players_objects_[j], true)) {
						j = -1;
						recalc_i = true;
						continue;
					}
				}
			}
			
			for (j = i+1; j < Enemy_objects_.size(); j++) {
				if (Enemy_objects_[i]->SafeDistanceToCollision(Enemy_objects_[j]) < 0) {
					if (!Enemy_objects_[i]->Collision(Enemy_objects_[j], true)) {
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
