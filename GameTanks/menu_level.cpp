#include "levels.h"

MenuLevel::MenuLevel() {
	this->SetBackgroundTexture("Data/background/background.png");
	this->SetBackgroundMusic("Data/Audio/music/Start_fon.ogg", 75);

	float a = 50, m = 3;
	NewGame_ =				new Button(sf::Vector2f(a, a + a * m * 0), sf::Vector2f(0, 0));
	ConnectToGameInput_ =	new Button(sf::Vector2f(a, a + a * m * 2), sf::Vector2f(0, 0));
	ConnectToGame_ =		new Button(sf::Vector2f(a, a + a * m * 1), sf::Vector2f(0, 0));
	Exit_ =					new Button(sf::Vector2f(a, a + a * m * 3), sf::Vector2f(0, 0));

	sf::Vector2f button_scale = sf::Vector2f(0.8f, 0.6f);
	NewGame_->SetScale(button_scale);
	ConnectToGameInput_->SetScale(button_scale);
	ConnectToGame_->SetScale(button_scale);
	Exit_->SetScale(button_scale);

	int text_size = 40;
	NewGame_->SetCharacterSize(text_size);
	ConnectToGameInput_->SetCharacterSize(text_size);
	ConnectToGame_->SetCharacterSize(text_size);
	Exit_->SetCharacterSize(text_size);

	float text_align = 0;
	NewGame_->SetTextAlign(0);
	ConnectToGameInput_->SetTextAlign(text_align);
	ConnectToGame_->SetTextAlign(0);
	Exit_->SetTextAlign(0);

	NewGame_->SetText("NEW GAME");
	ConnectToGameInput_->SetText("127.0.0.1");
	ConnectToGame_->SetText("CONNECT GAME");
	Exit_->SetText("EXIT");

	ConnectToGameInput_->SetFocusable(true);
	ConnectToGameInput_->ShowCursorBlink(true);

	this->AddUiObject(NewGame_);
	this->AddUiObject(ConnectToGameInput_);
	this->AddUiObject(ConnectToGame_);
	this->AddUiObject(Exit_);

	Title_ = new Title(sf::Vector2f(0, 100), sf::Vector2f(0, 0));
	Title_->SetScale(sf::Vector2f(0.5f, 0.5f));
	Title_->SetStartCoorditateCentre();
	Title_->SetStartCoorditateBottom();
	Title_->SetOffsetSprite(sf::Vector2f(Title_->GetWidthSprite(true) / 2.0f,
		Title_->GetHeightSprite(true)));
	this->AddUiObject(Title_);
}

bool MenuLevel::UpdateState(float& game_timer) {
	bool result = BaseLevel::UpdateState(game_timer);

	return result;
}

bool MenuLevel::ExitLevel(sf::Packet& Result_level) {
	bool result = BaseLevel::ExitLevel(Result_level);
	if (NewGame_->GetMouseUpOnThis(true)) {
		Result_level << Level_type::GAME_LEVEL;
		Result_level << "";
		return true;
	}
	else if (ConnectToGame_->GetMouseUpOnThis(true)) {
		Result_level << Level_type::GAME_LEVEL;
		Result_level << ConnectToGameInput_->GetText();
		return true;
	}
	else if (Exit_->GetMouseUpOnThis(true)) {
		Result_level << Level_type::EXIT;
		return true;
	}
	return result;
}
