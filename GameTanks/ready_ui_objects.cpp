#include "ready_objects.h"

Button::Button(sf::Vector2f const& coordinate_centre, 
	sf::Vector2f const& offset_sprite_coordinate) : UiObject(
			coordinate_centre, offset_sprite_coordinate,
			"Data/Ui/Button1.png", //texture
			5, 2){ //frame count
	this->SetFocusable(false);
	this->AddAudioAction("action1","Data/Audio/A1.ogg");
	this->AddAudioAction("action2", "Data/Audio/A1.ogg");
}

void Button::PlayAnimateEnter() {
	this->StartPlayAnimation(2, 1, 5, 30);
	this->StartAudioAction("action1");
}

void Button::PlayAnimateLeave() {
	this->StartPlayAnimation(2, 5, 1, 30);
	this->StartAudioAction("action2");
}

void Button::PlayAnimateClickDown() {
	this->StartPlayAnimation(1, 1, 5, 20);
}

void Button::PlayAnimateClickUp() {
	this->StartPlayAnimation(1, 5, 1, 20);
}

