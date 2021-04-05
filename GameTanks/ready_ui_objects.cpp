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

TextLine::TextLine(sf::Vector2f const& coordinate_centre, int const& width,
		int const& line_count,
		int const& one_line_text_size,
		int const& one_line_ui_size_px, int const& line_step_px)
	: UiObject(coordinate_centre, sf::Vector2f(0, 0),
		"Data/Ui/text_background_.png",
		1, 1) {
	width_ = width;
	one_line_text_size_ = one_line_text_size;
	one_line_ui_size_px_ = one_line_ui_size_px;
	line_step_px_ = line_step_px;
	this->ChangeCounLine(line_count);
	this->SetFocusable(false);
}

void TextLine::TextAlign(int const& align) {
	for (int i = 0; i < (int)Lines_.size(); i++) {
		Lines_[i]->SetTextAlign(align);
	}
}

void TextLine::ChangeCounLine(int const& line_count) {
	if (line_count > 0) {
		if (line_count > (int)Lines_.size()) {
			for (int i = (int)Lines_.size(); i < line_count; i++) {
				Lines_.push_back(new Text(sf::Vector2f(0, line_step_px_ * i)));
				Lines_.back()->SetText("");
				Lines_.back()->SetTexture("Data/Ui/text_background_.png", 1, 1);
				Lines_.back()->SetCharacterSize(one_line_text_size_);
				Lines_.back()->SetAnchorObject(this);
				Lines_.back()->SetScale(sf::Vector2f(
					width_ / (float)Lines_.back()->GetWidthSprite(),
					one_line_ui_size_px_ / (float)Lines_.back()->GetHeightSprite()));
			}
			this->SetScale(sf::Vector2f(
				width_ / (float)this->GetWidthSprite(),
				(line_count * line_step_px_ -
					(line_step_px_ - one_line_ui_size_px_)) 
				/ (float)this->GetHeightSprite()));
		}
		else if (line_count < (int)Lines_.size()) {
			for (int i = (int)Lines_.size(); i > line_count; i--) {
				delete Lines_.back();
				Lines_.pop_back();
			}
			this->SetScale(sf::Vector2f(
				width_ / (float)this->GetWidthSprite(),
				(line_count* line_step_px_ -
					(line_step_px_ - one_line_ui_size_px_))
				/ (float)this->GetHeightSprite()));
		}
	}
}

void TextLine::SetTextLine(std::string str, int const& line_number) {
	if (line_number >= 0 && line_number < (int)Lines_.size())
		Lines_[line_number]->SetText(str);
}

void TextLine::Draw(sf::RenderWindow& window) {
	UiObject::Draw(window);
	for (int i = 0; i < (int)Lines_.size(); i++)
		Lines_[i]->Draw(window);
}

TextLine::~TextLine() {
	for (int i = 0; i < (int)Lines_.size(); i++)
		delete Lines_[i];
}

/*--------------------------*/