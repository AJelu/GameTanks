#include "ready_objects.h"

Button::Button(sf::Vector2f const& coordinate_centre, 
	sf::Vector2f const& offset_sprite_coordinate) : UiObject(
			coordinate_centre, offset_sprite_coordinate,
			"Data/Ui/Button2.png", //texture
			3, 1){ //frame count
	this->SetFocusable(false);
	this->AddAudioAction("action1","Data/Audio/button_click/Button_click.ogg");
	this->AddAudioAction("action2", "Data/Audio/button_click/Button_pressed.ogg");
}

void Button::ActionEnter() {
	this->StartPlayAnimation(1, 1, 3, 30);
	this->StartAudioAction("action1");
}

void Button::ActionLeave() {
	this->StartPlayAnimation(1, 3, 1, 30);
	this->StartAudioAction("action2");
}

void Button::ActionClickDown() {
	this->StartPlayAnimation(1, 1, 3, 20);
}

void Button::ActionClickUp() {
	this->StartPlayAnimation(1, 3, 1, 20);
}

