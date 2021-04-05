#include "ready_objects.h"

Button::Button(sf::Vector2f const& coordinate_centre, 
	sf::Vector2f const& offset_sprite_coordinate) : UiObject(
			coordinate_centre, offset_sprite_coordinate,
			"Data/Ui/Button.png", //texture
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

Loading::Loading(sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate) : UiObject(
		coordinate_centre, offset_sprite_coordinate,
		"Data/Ui/loading.png", //texture
		1, 1) { //frame count
}

Title::Title(sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate) : UiObject(
		coordinate_centre, offset_sprite_coordinate,
		"Data/Ui/title.png", //texture
		2, 1) { //frame count
	this->SetFocusable(false);
	this->AddAudioAction("action1", "Data/Audio/button_click/Button_click.ogg");
	this->AddAudioAction("action2", "Data/Audio/button_click/Button_pressed.ogg");
}

void Title::ActionEnter() {
	this->StartPlayAnimation(1, 1, 2, 20);
	this->StartAudioAction("action1");
}

void Title::ActionLeave() {
	this->StartPlayAnimation(1, 2, 1, 20);
	this->StartAudioAction("action2");
}

/*-------example:-----------*/
Text::Text(sf::Vector2f const& coordinate_centre) : UiObject(
	coordinate_centre, sf::Vector2f(0, 0),
	"Data/Ui/text_background.png", //texture<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	1, 1) {
}

void Text::ActionEnter()
{
}

void Text::ActionLeave()
{
}

void Text::ActionClickDown()
{
}

void Text::ActionClickUp()
{
}

PlayersTextBackground::PlayersTextBackground(sf::Vector2f const& coordinate_centre) 
	: UiObject(coordinate_centre, sf::Vector2f(0, 0),
	"Data/Ui/player_text_background.png",
	1, 1) {
}

TextLine::TextLine(sf::Vector2f const& coordinate_centre, 
		int const& line_count, int const& one_line_text_size, int const& line_step_px)
	: UiObject(coordinate_centre, sf::Vector2f(0, 0),
		"Data/Ui/text_background.png",
		1, 1) {
	this->SetFocusable(false);
	for (int i = 0; i < line_count; i++) {
		Lines_.push_back(Text(sf::Vector2f(10, line_step_px * i)));
		Lines_.back().SetText("");
		Lines_.back().SetCharacterSize(one_line_text_size);
		Lines_.back().SetAnchorObject(this);
	}
}

void TextLine::ActionEnter()
{
}

void TextLine::ActionLeave()
{
}

void TextLine::ActionClickDown()
{
}

void TextLine::ActionClickUp()
{
}

void TextLine::SetTextLine(std::string str, int const& line_number) {
	Lines_[line_number].SetText(str);
}

void TextLine::Draw(sf::RenderWindow& window) {
	UiObject::Draw(window);
	for (int i = 0; i < (int)Lines_.size(); i++)
		Lines_[i].Draw(window);
}

/*--------------------------*/