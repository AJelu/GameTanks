#pragma once

class BaseCollision
{
private:
	int x_, y_;
	float rotation_by_gradus_;
public:
	BaseCollision();
	BaseCollision(int x_coordinate, int y_coordinate);

	int GetCoordinateX();
	int GetCoordinateY();
	int GetCoordinateByRotateX();
	int GetCoordinateByRotateY();
	void SetCoordinate(int x_coordinate, int y_coordinate);

	virtual void SetRotation(float rotation_by_gradus);

	//check if coordinate is in figure
	virtual bool CoordinatesInFigure(int x_coordinate, int y_coordinate) = 0;
	//virtual float DistanceToCollision(int x_coordinate, int y_coordinate);
};

class RoundCollision : public BaseCollision
{
private:
	int r_;

public:
	RoundCollision();
	RoundCollision(int x_coordinate, int y_coordinate, int radius);

	int GetRadius();
	void SetRadius(int radius);

	bool CoordinatesInFigure(int x_coordinate, int y_coordinate) override;
	//virtual float DistanceToCollision(int x_coordinate, int y_coordinate) override;
	float DistanceToCollision(RoundCollision collision);
};