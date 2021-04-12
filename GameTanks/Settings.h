#pragma once
#include <SFML/Graphics.hpp>

/* ENGINE SETTINGS: */
static const int GAME_SPEED_CONTROLLER = 1000;

static const float SCREEN_RESOLUTION_X = float(sf::VideoMode::getDesktopMode().width);
static const float SCREEN_RESOLUTION_Y = float(sf::VideoMode::getDesktopMode().height);

/* PLAYER-ENEMY SETTINGS: */
static const int ENEMY_SHOT_TIME_MULTIPLY = 5;
static const int ENEMY_ROTATION_DEGREE = 180;
static const int ENEMY_DISTANCE_MOVE = 200;

static const int TIME_TO_RESPAWN = 5000;

static const int TIME_DURATION_BONUS = 100000;

static const float TRANSFER_PERCENTAGE_POINT = 0.10f;