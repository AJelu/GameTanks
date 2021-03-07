#include "collisions.h"

BaseCollision::BaseCollision()
{
    SetCoordinate(Vector2f(0, 0));
}

BaseCollision::BaseCollision(Vector2f const& coordinate)
{
    SetCoordinate(coordinate);
}

Vector2f BaseCollision::GetCoordinate() { return coordinate_; }

void BaseCollision::SetCoordinate(Vector2f const& coordinate)
{ coordinate_ = coordinate; }



RoundCollision::RoundCollision() : BaseCollision() { r_ = 1; }

RoundCollision::RoundCollision(Vector2f const& coordinate, float const& radius) : BaseCollision(coordinate)
{ r_ = radius; }

float RoundCollision::GetRadius() { return r_; }

void RoundCollision::SetRadius(float const& radius) 
{ r_ = radius; }

bool RoundCollision::CoordinatesInFigure(Vector2f const& coordinate)
{
    return false;
}
