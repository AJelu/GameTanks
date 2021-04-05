#include "levels.h"

LoadLevel::LoadLevel(std::string const& text) {
	this->SetBackgroundTexture("Data/background/background.png");
	Button* Exit_ = new Button(sf::Vector2f(20, 20), sf::Vector2f(0, 0));
	Exit_->SetTextAlign(0);
	Exit_->SetCharacterSize(50);
	Exit_->SetText(text);
	this->AddUiObject(Exit_);
}