#include "ready_objects.h"

Button::Button(sf::Vector2f const& coordinate_centre, 
	sf::Vector2f const& offset_sprite_coordinate) : UiObject(
			coordinate_centre, offset_sprite_coordinate,
			"Data/Ui/Button1.png", //texture
			5, 2){ //frame count
	this->SetFocusable(false);
}

void Button::PlayAnimateEnter() {
	StartPlayAnimation(2, 1, 5, 30);
}

void Button::PlayAnimateLeave() {
	StartPlayAnimation(2, 5, 1, 30);
}

void Button::PlayAnimateClickDown() {
	StartPlayAnimation(1, 1, 5, 20);
}

void Button::PlayAnimateClickUp() {
	StartPlayAnimation(1, 5, 1, 20);
}

