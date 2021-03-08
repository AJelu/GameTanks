#include "objects.h"

UiObject::UiObject() : VisibleObject() {
	coordinate_centre_.x = 0;
	coordinate_centre_.x = 0;
	Camera_ = nullptr;
}

UiObject::UiObject(int const& id_object,
	sf::Vector2f const& coordinate_centre, sf::View* Camera,
	sf::Vector2f const& offset_sprite_coordinate,
	std::string const& texture, int const& frame_count_x, int const& frame_count_y)
	: VisibleObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y) {
	coordinate_centre_ = coordinate_centre;
	Camera_ = Camera;
}

bool UiObject::IsFocusOnThis(int const& x, int const& y) {
	return false;
}

bool UiObject::IsDownOnThis(int const& x, int const& y) {
	return false;
}

bool UiObject::IsUpOnThis(int const& x, int const& y) {
	return false;
}

void UiObject::AddInputText(std::string const& text) { text_ += text; }

void UiObject::SetText(std::string const& text) { text_ = text; }

bool UiObject::GetFocusOnThis(bool clear) {
	bool b = focus_on_this_;
	focus_on_this_ = focus_on_this_ && !clear;
	return b;
}

bool UiObject::GetDownOnThis(bool clear) {
	bool b = down_on_this_;
	down_on_this_ = down_on_this_ && !clear;
	return b;
}

bool UiObject::GetUpOnThis(bool clear) {
	bool b = up_on_this_;
	up_on_this_ = up_on_this_ && !clear;
	return b;
}

std::string UiObject::GetText(){
	std::string b = text_;
	text_ = "";
	return b;
}

void UiObject::Draw(sf::RenderWindow& window) {
}
