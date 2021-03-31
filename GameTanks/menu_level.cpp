#include "levels.h"

MenuLevel::MenuLevel() {
	float a = 20, m = 3;
	NewGame_ =				new Button(sf::Vector2f(a, a + a * m * 0), sf::Vector2f(0, 0));
	ConnectToGameInput_ =	new Button(sf::Vector2f(a, a + a * m * 2), sf::Vector2f(0, 0));
	ConnectToGame_ =		new Button(sf::Vector2f(a, a + a * m * 1), sf::Vector2f(0, 0));
	Exit_ =					new Button(sf::Vector2f(a, a + a * m * 3), sf::Vector2f(0, 0));

	sf::Vector2f scale = sf::Vector2f(0.5f, 0.3f);
	NewGame_->SetScale(scale);
	ConnectToGameInput_->SetScale(scale);
	ConnectToGame_->SetScale(scale);
	Exit_->SetScale(scale);

	int text_size = 20;
	NewGame_->SetCharacterSize(text_size);
	ConnectToGameInput_->SetCharacterSize(text_size);
	ConnectToGame_->SetCharacterSize(text_size);
	Exit_->SetCharacterSize(text_size);

	float text_align = -0.01f;
	NewGame_->SetTextAlign(0);
	ConnectToGameInput_->SetTextAlign(text_align);
	ConnectToGame_->SetTextAlign(0);
	Exit_->SetTextAlign(0);

	NewGame_->SetText("NewGame");
	ConnectToGameInput_->SetText("127.0.0.1");
	ConnectToGame_->SetText("ConnectToGame");
	Exit_->SetText("Exit");

	ConnectToGameInput_->SetFocusable(true);
	ConnectToGameInput_->ShowCursorBlink(true);

	this->AddUiObject(NewGame_);
	this->AddUiObject(ConnectToGameInput_);
	this->AddUiObject(ConnectToGame_);
	this->AddUiObject(Exit_);
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
