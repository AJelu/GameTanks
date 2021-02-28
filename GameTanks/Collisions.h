#pragma once

class BaseCollision
{
private:
	int x_, y_;
	float rotation_vector_x_, rotation_vector_y_;
	//for optimisation:
	bool set_new_vector;
	int temp_x_, temp_y_;
public:
	BaseCollision();
	BaseCollision(int x_coordinate, int y_coordinate);

	int GetCoordinateX();
	int GetCoordinateY();
	int GetCoordinateByRotateX();
	int GetCoordinateByRotateY();

	void SetCoordinate(int x_coordinate, int y_coordinate);
	virtual void SetRotation(float rotation_vector_x, float rotation_vector_y);

	//check if coordinate is in figure
	virtual bool CoordinatesInFigure(int x_coordinate, int y_coordinate) = 0;
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
};