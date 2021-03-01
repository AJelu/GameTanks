#include "objects.h"

UiObject::UiObject() : VisibleObject() {}
UiObject::UiObject(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	string const& texture, int const& frame_count_x, int const& frame_count_y)
	: VisibleObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y)
{

}

bool UiObject::IsFocusOnThis(int const& x, int const& y)
{
	return false;
}

bool UiObject::IsDownOnThis(int const& x, int const& y)
{
	return false;
}

bool UiObject::IsUpOnThis(int const& x, int const& y)
{
	return false;
}

void UiObject::AddInputText(string const& text) { text_ += text; }
void UiObject::SetText(string const& text) { text_ = text; }


bool UiObject::GetFocusOnThis() 
{
	bool b = focus_on_this_;
	focus_on_this_ = false;
	return b;
}
bool UiObject::GetDownOnThis() 
{
	bool b = down_on_this_;
	down_on_this_ = false;
	return b;
}
bool UiObject::GetUpOnThis() 
{
	bool b = up_on_this_;
	up_on_this_ = false;
	return b;
}
string UiObject::GetText() 
{
	string b = text_;
	text_ = "";
	return b;
}