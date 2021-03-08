#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class BaseCollision
{
private:
	Vector2f coordinate_;
public:
	BaseCollision();
	BaseCollision(Vector2f const& coordinate);

	Vector2f GetCoordinate();

	void SetCoordinate(Vector2f const& coordinate);

	//check if coordinate is in figure
	virtual bool CoordinatesInFigure(Vector2f const& coordinate) = 0;
};

class RoundCollision : public BaseCollision
{
private:
	float r_;

public:
	RoundCollision();
	RoundCollision(Vector2f const& coordinate, float const& radius);

	float GetRadius();
	void SetRadius(float const& radius);

	bool CoordinatesInFigure(Vector2f const& coordinate) override;
};