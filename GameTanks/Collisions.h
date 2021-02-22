#pragma once

class BaseCollision
{
public:
	//check if coordinate is in figure
	virtual bool CoordinatesInFigure(int x_coordinate, int y_coordinate);
};

class RoundCollision : BaseCollision
{
private:
	int x_, y_, r_;

public:
	RoundCollision(int x_coordinate, int y_coordinate, int radius);

	int GetCoordinateX();
	int GetCoordinateY();
	int GetRadius();

	int SetCoordinate(int x_coordinate, int y_coordinate);
	int SetRadius(int radius);

	//virtual function
};