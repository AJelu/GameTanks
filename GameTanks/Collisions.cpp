#define _USE_MATH_DEFINES
#include <cmath>
#include "collisions.h"

BaseCollision::BaseCollision() { SetCoordinate(sf::Vector2f(0, 0)); }

BaseCollision::BaseCollision(sf::Vector2f const& coordinate) { 
    SetCoordinate(coordinate); }

sf::Vector2f BaseCollision::GetCoordinate() { return coordinate_; }

sf::Vector2f BaseCollision::GetCoordinateByRotation(float const& rotation_degree)
{
    if (rotation_degree != rotation_degree_) {
		float to_radian = (-rotation_degree) * (float)M_PI / 180.0f;
		coordinate_by_rotation_.x = (coordinate_.x * cos(to_radian) -
			coordinate_.y * sin(to_radian));
		coordinate_by_rotation_.y = (coordinate_.x * sin(to_radian) +
			coordinate_.y * cos(to_radian));
        rotation_degree_ = rotation_degree;
    }
    return coordinate_by_rotation_;
}

void BaseCollision::SetCoordinate(sf::Vector2f const& coordinate) { 
    coordinate_ = coordinate; }

RoundCollision::RoundCollision() : BaseCollision() { r_ = 1; }

RoundCollision::RoundCollision(sf::Vector2f const& coordinate, float const& radius) 
    : BaseCollision(coordinate) { 
    r_ = radius; 
}

float RoundCollision::GetRadius() { return r_; }

void RoundCollision::SetRadius(float const& radius) { r_ = radius; }

bool RoundCollision::CoordinatesInFigure(sf::Vector2f const& coordinate) { return false; }
