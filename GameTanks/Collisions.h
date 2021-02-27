#pragma once

class BaseCollision
{
private:
	int x_, y_;
public:
	int GetCoordinateX();
	int GetCoordinateY();
	void SetCoordinate(int x_coordinate, int y_coordinate);

	//check if coordinate is in figure
	virtual bool CoordinatesInFigure(int x_coordinate, int y_coordinate);
	//virtual float DistanceToCollision(int x_coordinate, int y_coordinate);
};

class RoundCollision : BaseCollision
{
private:
	int r_;

public:
	RoundCollision(int x_coordinate, int y_coordinate, int radius);

	int GetRadius();
	void SetRadius(int radius);

	virtual bool CoordinatesInFigure(int x_coordinate, int y_coordinate) override;
	//virtual float DistanceToCollision(int x_coordinate, int y_coordinate) override;
	float DistanceToCollision(RoundCollision collision);
};