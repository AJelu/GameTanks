#include "collisions.h"

BaseCollision::BaseCollision()
{
    x_ = 0;
    y_ = 0;
}

BaseCollision::BaseCollision(int x_coordinate, int y_coordinate)
{ SetCoordinate(x_coordinate, y_coordinate); }

int BaseCollision::GetCoordinateX() { return x_; }
int BaseCollision::GetCoordinateY() { return y_; }
int BaseCollision::GetCoordinateByRotateX()
{
    //calculate rorate;
    return x_;
}

int BaseCollision::GetCoordinateByRotateY()
{
    //calculate rorate;
    return y_;
}

void BaseCollision::SetCoordinate(int x_coordinate, int y_coordinate)
{
    x_ = x_coordinate;
    y_ = y_coordinate;
}

void BaseCollision::SetRotation(float rotation_by_gradus)
{
    rotation_by_gradus_ = rotation_by_gradus;
}

RoundCollision::RoundCollision() : BaseCollision() { r_ = 1; }

RoundCollision::RoundCollision(int x_coordinate, int y_coordinate, int radius) : BaseCollision(x_coordinate, y_coordinate) 
{ r_ = radius; }

int RoundCollision::GetRadius() { return r_; }

void RoundCollision::SetRadius(int radius) { r_ = radius; }

bool RoundCollision::CoordinatesInFigure(int x_coordinate, int y_coordinate)
{
    return false;
}

float RoundCollision::DistanceToCollision(RoundCollision collision)
{
    return 0.0f;
}
