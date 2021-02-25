#pragma once
#include "Objects.h"
#include <vector>

class BaseLevel
{
private:
	std::vector <UiObject>* ui_objects_;
	std::vector <GameObject>* game_objects_;
	std::vector <TankObject>* enemy_objects_;
	std::vector <MovebleObject>* shot_objects_;
	int size_level_height, size_level_width;

public:
	void Draw(sf::RenderWindow* window);

	void AddUiObject(UiObject ui_object);
	void AddUiObject(GameObject game_objects);
	void AddUiObject(TankObject enemy_objects);
	void AddUiObject(MovebleObject shot_objects);

	UiObject* GetUiObjects();
	GameObject* GetGameObjects();
	TankObject* GetEnemyObjects();
	MovebleObject* GetTempObjects();

	bool Input(/**/);

	void InputEnemy();

	bool CalculateCollisionOnLevel();

	bool /*message*/ EndLevel();
};

class MenuLevel : BaseLevel
{

};

class ConnectLevel : BaseLevel
{

};

class GameLevel : BaseLevel
{
private:
	TankObject watching_object;
	TankObject oponent_object;
};