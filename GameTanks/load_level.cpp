#include "levels.h"

LoadLevel::LoadLevel(std::string const& text) {
	this->SetBackgroundTexture("Data/background/background.png");
	Loading* Exit_ = new Loading(sf::Vector2f(500, 850), sf::Vector2f(0, 0));
	Exit_->SetTextAlign(0);
	Exit_->SetCharacterSize(50);
	Exit_->SetText(text);
	this->AddUiObject(Exit_);
}