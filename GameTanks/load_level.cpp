#include "levels.h"

LoadLevel::LoadLevel(std::string const& text) : BaseLevel() {
	this->SetBackgroundTexture("Data/background/background.png");
	Loading* Text_item = new Loading(sf::Vector2f(0, 100), sf::Vector2f(0, 0));
	Text_item->SetStartCoorditateCentre();
	Text_item->SetStartCoorditateBottom();
	Text_item->SetOffsetSprite(sf::Vector2f(Text_item->GetWidthSprite(true) / 2.0f,
		(float)Text_item->GetHeightSprite(true)));
	Text_item->SetTextAlign(0);
	Text_item->SetCharacterSize(50);
	Text_item->SetText(text);
	this->AddUiObject(Text_item);
}