#pragma once
#include <SFML/Graphics.hpp>

/* The file contains the basic settings of the game */

/* ENGINE: */
static const int GAME_SPEED_CONTROLLER = 1000;
static const int GAME_TIMER_LIMIT = 1;

static const float SCREEN_RESOLUTION_X = 1024; //float(sf::VideoMode::getDesktopMode().width); //
static const float SCREEN_RESOLUTION_Y = 768; //float(sf::VideoMode::getDesktopMode().height); //


//enemy settings:
static const int ENEMY_SHOT_TIME_MULTIPLY = 5;
static const int ENEMY_ROTATION_DEGREE = 180;
static const int ENEMY_DISTANCE_MOVE = 200;


static const int TIME_TO_RESPAWN = 5000;

static const int TIME_DURATION_BONUS = 100000;

static const float TRANSFER_PERCENTAGE_POINT = 0.10f;

/* GAME: */
//here may be the basic settings of the game... 
//may be speed attack/number of enemies/number of objects...