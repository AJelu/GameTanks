#include "objects.h"

UiObject::UiObject() : VisibleObject() {}
UiObject::UiObject(int id_object,
	sf::Vector2f coordinate_centre,
	sf::Vector2f offset_sprite_coordinate,
	string texture, int frame_count_x, int frame_count_y)
	: VisibleObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y)
{
	//On_mouse_up_action_ = On_mouse_up_action;
}

bool UiObject::IsFocusOnThis(int x, int y)
{
	return false;
}

bool UiObject::IsDownOnThis(int x, int y)
{
	return false;
}

bool UiObject::IsUpOnThis(int x, int y)
{
	return false;
}

void UiObject::AddInputText(string text) { text_ += text; }
void UiObject::SetText(string text) { text_ = text; }


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

UiObject::~UiObject()
{
	// delete BaseAction* On_mouse_up_action_;
}