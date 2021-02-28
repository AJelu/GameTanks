#include "collisions.h"

BaseCollision::BaseCollision()
{
    SetCoordinate(0, 0);
    SetRotation(0.0f, 1.0f);
}

BaseCollision::BaseCollision(int x_coordinate, int y_coordinate)
{
    SetCoordinate(x_coordinate, y_coordinate);
    SetRotation(0.0f, 1.0f);
}

int BaseCollision::GetCoordinateX() { return x_; }
int BaseCollision::GetCoordinateY() { return y_; }
int BaseCollision::GetCoordinateByRotateX()
{
    if (set_new_vector) {
        //calculate rorate and write to temp_x_;
        set_new_vector = false;
    }
    return temp_x_;
}

int BaseCollision::GetCoordinateByRotateY()
{
    if (set_new_vector) {
        //calculate rorate and write to temp_x_;
        set_new_vector = false;
    }
    return temp_y_;
}

void BaseCollision::SetCoordinate(int x_coordinate, int y_coordinate)
{
    x_ = x_coordinate;
    y_ = y_coordinate;
    set_new_vector = true;
}

void BaseCollision::SetRotation(float rotation_vector_x, float rotation_vector_y)
{
    rotation_vector_x_ = rotation_vector_x;
    rotation_vector_y_ = rotation_vector_y;
    set_new_vector = true;
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
