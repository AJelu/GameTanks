#pragma once
#include <SFML/Graphics.hpp>

class BaseCollision {
private:
	sf::Vector2f coordinate_;

public:
	BaseCollision();
	BaseCollision(sf::Vector2f const& coordinate);

	sf::Vector2f GetCoordinate();

	void SetCoordinate(sf::Vector2f const& coordinate);

	//check if coordinate is in figure
	virtual bool CoordinatesInFigure(sf::Vector2f const& coordinate) = 0;
};

class RoundCollision : public BaseCollision {
private:
	int r_;

public:
	RoundCollision();
	RoundCollision(sf::Vector2f const& coordinate, float const& radius);

	float GetRadius();
	void SetRadius(float const& radius);

	bool CoordinatesInFigure(sf::Vector2f const& coordinate) override;
};