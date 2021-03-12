#pragma once
#include <SFML/Graphics.hpp>

class BaseCollision {
private:
	sf::Vector2f coordinate_;
	sf::Vector2f coordinate_by_rotation_;
	float rotation_degree_;

public:
	BaseCollision();
	BaseCollision(sf::Vector2f const& coordinate);

	sf::Vector2f GetCoordinate();
	sf::Vector2f GetCoordinateByRotation(float const& rotation_degree);

	void SetCoordinate(sf::Vector2f const& coordinate);

	//check if coordinate is in figure
	virtual bool CoordinatesInFigure(sf::Vector2f const& coordinate) = 0;
};

class RoundCollision : public BaseCollision {
private:
	float r_;

public:
	RoundCollision();
	RoundCollision(sf::Vector2f const& coordinate, float const& radius);

	float GetRadius();
	void SetRadius(float const& radius);

	bool CoordinatesInFigure(sf::Vector2f const& coordinate) override;
};