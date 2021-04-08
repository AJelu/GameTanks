#include "objects.h"

UiObject::UiObject() : AudioObject() {
	coordinate_centre_.x = 0;
	coordinate_centre_.y = 0;

	Font_.loadFromFile("Data/Font/Font.ttf");
	Text_in_ui_.setFont(Font_);
	Text_color_ = sf::Color::Black;
	Text_style_ = sf::Text::Style::Regular;
	character_size_ = 30;
	cursor_size_ = 3; 
	show_cursor_ = focusable_ = false;
	this->SetText("");
	this->SetStartCoorditateLeft();
	this->SetStartCoorditateTop();
}

UiObject::UiObject(
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	std::string const& texture, int const& frame_count_x, int const& frame_count_y)
	: AudioObject(0, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y) {
	coordinate_centre_ = coordinate_centre;

	Font_.loadFromFile("Data/Font/Font.ttf");
	Text_in_ui_.setFont(Font_);
	Text_color_ = sf::Color::Black;
	Text_style_ = sf::Text::Style::Regular;
	character_size_ = 30;
	cursor_size_ = 3;
	show_cursor_ = focusable_ = false;
	this->SetText("");
	this->SetStartCoorditateLeft();
	this->SetStartCoorditateTop();
}

bool UiObject::MouseInputToObject(sf::Event::EventType const& event_type,
	sf::Vector2i const& mouse_position, bool keyboard_input) {
	sf::Vector2f mouse = sf::Vector2f((float)mouse_position.x, (float)mouse_position.y)
		- this->GetCoordinateCentre();
	mouse = this->ChangeVectorByDirection(mouse);
	mouse += this->GetOffsetSprite();

	if ((mouse.x >= 0 && mouse.x <= this->GetWidthSprite(true) &&
		mouse.y >= 0 && mouse.y <= this->GetHeightSprite(true)) || keyboard_input) {
		switch (event_type)
		{
		case sf::Event::EventType::MouseWheelMoved:
			break;
		case sf::Event::EventType::MouseWheelScrolled:
			break;
		case sf::Event::EventType::MouseButtonPressed:
			down_on_this_ = true;
			up_on_this_ = false;
			this->ActionClickDown();
			break;
		case sf::Event::EventType::MouseButtonReleased:
			if (down_on_this_) {
				down_on_this_ = false;
				up_on_this_ = true;
				this->ActionClickUp();
			}
			break;
		case sf::Event::EventType::MouseMoved:
			if (!enter_on_this_) {
				enter_on_this_ = true;
				leave_on_this_ = false;
								this->ActionEnter();
				if (down_on_this_)	this->ActionClickDown();
			}
			break;
		default:
			break;
		}
		return true;
	}
	else {
		if (enter_on_this_) {
			enter_on_this_ = false;
			leave_on_this_ = true;
			if (down_on_this_)	this->ActionClickUp();
			this->ActionLeave();
		}

		if (event_type == sf::Event::EventType::MouseButtonReleased)
			down_on_this_ = false;
	}
	return false;
}

void UiObject::InputKey(sf::Keyboard::Key const& key) {
	switch (key) {
	case sf::Keyboard::Key::A: this->SetText("A", true); break;
	case sf::Keyboard::Key::B: this->SetText("B", true); break;
	case sf::Keyboard::Key::C: this->SetText("C", true); break;
	case sf::Keyboard::Key::D: this->SetText("D", true); break;
	case sf::Keyboard::Key::E: this->SetText("E", true); break;
	case sf::Keyboard::Key::F: this->SetText("F", true); break;
	case sf::Keyboard::Key::G: this->SetText("G", true); break;
	case sf::Keyboard::Key::H: this->SetText("H", true); break;
	case sf::Keyboard::Key::I: this->SetText("I", true); break;
	case sf::Keyboard::Key::J: this->SetText("J", true); break;
	case sf::Keyboard::Key::K: this->SetText("K", true); break;
	case sf::Keyboard::Key::L: this->SetText("L", true); break;
	case sf::Keyboard::Key::M: this->SetText("M", true); break;
	case sf::Keyboard::Key::N: this->SetText("N", true); break;
	case sf::Keyboard::Key::O: this->SetText("O", true); break;
	case sf::Keyboard::Key::P: this->SetText("P", true); break;
	case sf::Keyboard::Key::Q: this->SetText("Q", true); break;
	case sf::Keyboard::Key::R: this->SetText("R", true); break;
	case sf::Keyboard::Key::S: this->SetText("S", true); break;
	case sf::Keyboard::Key::T: this->SetText("T", true); break;
	case sf::Keyboard::Key::U: this->SetText("U", true); break;
	case sf::Keyboard::Key::V: this->SetText("V", true); break;
	case sf::Keyboard::Key::W: this->SetText("W", true); break;
	case sf::Keyboard::Key::X: this->SetText("X", true); break;
	case sf::Keyboard::Key::Y: this->SetText("Y", true); break;
	case sf::Keyboard::Key::Z: this->SetText("Z", true); break;
	case sf::Keyboard::Key::Space: this->SetText(" ", true); break;
	//case sf::Keyboard::Key::Period:
	case sf::Keyboard::Key::Period: this->SetText(".", true); break;
	case sf::Keyboard::Key::Backspace: 
		if (text_.length() > 0) {
			text_.erase(text_.end() - 1, text_.end());
			this->SetText(text_);
		}
		break;
	case sf::Keyboard::Key::Num0:
	case sf::Keyboard::Key::Numpad0: this->SetText("0", true); break;
	case sf::Keyboard::Key::Num1:
	case sf::Keyboard::Key::Numpad1: this->SetText("1", true); break;
	case sf::Keyboard::Key::Num2:
	case sf::Keyboard::Key::Numpad2: this->SetText("2", true); break;
	case sf::Keyboard::Key::Num3:
	case sf::Keyboard::Key::Numpad3: this->SetText("3", true); break;
	case sf::Keyboard::Key::Num4:
	case sf::Keyboard::Key::Numpad4: this->SetText("4", true); break;
	case sf::Keyboard::Key::Num5:
	case sf::Keyboard::Key::Numpad5: this->SetText("5", true); break;
	case sf::Keyboard::Key::Num6:
	case sf::Keyboard::Key::Numpad6: this->SetText("6", true); break;
	case sf::Keyboard::Key::Num7:
	case sf::Keyboard::Key::Numpad7: this->SetText("7", true); break;
	case sf::Keyboard::Key::Num8:
	case sf::Keyboard::Key::Numpad8: this->SetText("8", true); break;
	case sf::Keyboard::Key::Num9:
	case sf::Keyboard::Key::Numpad9: this->SetText("9", true); break;
	default:
		break;
	}

}

void UiObject::RecalculateState(float const& game_time) {
	AudioObject::RecalculateState(game_time);
	time_blink_cursor_ += game_time;
	if (time_blink_cursor_ > 1000) time_blink_cursor_ = 0;
}

void UiObject::SetText(std::string text, bool const& add_to_previous) { 
	if (add_to_previous)	text_ += text;
	else					text_ = text;
	time_blink_cursor_ = 0;
	Text_in_ui_.setString(text_);
}

void UiObject::ShowCursorBlink(bool const& show_cursor) { 
	show_cursor_ = show_cursor && focusable_;
	time_blink_cursor_ = 0;
}

void UiObject::SetTextColor(sf::Color const& Text_color) { Text_color_ = Text_color; }

void UiObject::SetTextStyle(sf::Text::Style const& Text_style) {
	Text_style_ = Text_style;
}

void UiObject::SetCharacterSize(unsigned int const& character_size) {
	character_size_ = character_size;
}

void UiObject::SetCursorSize(float const& cursor_size) { cursor_size_ = cursor_size; }

void UiObject::SetFocusable(bool const& focusable) { focusable_ = focusable; }

void UiObject::SetTextAlign(float const& align) { text_centre_ = align; }

void UiObject::SetStartCoorditateLeft() { centring_x = LEFT; }

void UiObject::SetStartCoorditateRight() { centring_x = RIGHT; }

void UiObject::SetStartCoorditateCentre() { centring_x = CENTER; }

void UiObject::SetStartCoorditateTop() { centring_y = TOP; }

void UiObject::SetStartCoorditateMiddle() { centring_y = MIDDLE; }

void UiObject::SetStartCoorditateBottom() { centring_y = BOTTOM; }

std::string UiObject::GetText(){ return text_; }

bool UiObject::GetCursorBlink() { return show_cursor_; }

sf::Color UiObject::GetTextColor() { return Text_color_; }

sf::Text::Style UiObject::GetTextStyle() { return Text_style_; }

unsigned int UiObject::GetCharacterSize() { return character_size_; }

float UiObject::GetCursorSize() { return cursor_size_; }

bool UiObject::GetFocusable() { return focusable_; }

float UiObject::GetTextAlign() { return text_centre_; }

bool UiObject::GetMouseDownOnThis(bool clear) {
	bool b = down_on_this_;
	down_on_this_ = down_on_this_ && !clear;
	return b;
}

bool UiObject::GetMouseUpOnThis(bool clear) {
	bool b = up_on_this_;
	up_on_this_ = up_on_this_ && !clear;
	return b;
}

void UiObject::SetAnchorObject(VisibleObject* Anchor_object) { 
	Anchor_object_ = Anchor_object; 
}

VisibleObject* UiObject::GetAnchorObject() { return Anchor_object_; }

void UiObject::ActionEnter() { }

void UiObject::ActionLeave() { }

void UiObject::ActionClickDown() { }

void UiObject::ActionClickUp() { }

void UiObject::Draw(sf::RenderWindow& window) {

	if (Anchor_object_ != nullptr) {
		this->SetCoordinate(Anchor_object_->GetCoordinateCentre() + coordinate_centre_);
	}
	else if (this->GetCamera() != nullptr) {
		float coordinate_x = 0, coordinate_y = 0;
		if (centring_x == LEFT) {
			coordinate_x = this->GetCamera()->getCenter().x
				- this->GetCamera()->getSize().x / 2.f
				+ coordinate_centre_.x;
		}
		else if (centring_x == CENTER) {
			coordinate_x = this->GetCamera()->getCenter().x
				+ coordinate_centre_.x;
		}
		else if (centring_x == RIGHT) {
			coordinate_x = this->GetCamera()->getCenter().x
				+ this->GetCamera()->getSize().x / 2.f
				- coordinate_centre_.x;
		}
		if (centring_y == TOP) {
			coordinate_y = this->GetCamera()->getCenter().y
				- this->GetCamera()->getSize().y / 2.f
				+ coordinate_centre_.y;
		}
		else if (centring_y == MIDDLE) {
			coordinate_y = this->GetCamera()->getCenter().y
				+ coordinate_centre_.y;
		}
		else if (centring_y == BOTTOM) {
			coordinate_y = this->GetCamera()->getCenter().y
				+ this->GetCamera()->getSize().y / 2.f
				- coordinate_centre_.y;
		}
		this->SetCoordinate(sf::Vector2f(coordinate_x, coordinate_y));
	}
	else {
		this->SetCoordinate(coordinate_centre_);
	}
	AudioObject::Draw(window);

	//draw text:
	Text_in_ui_.setCharacterSize(character_size_);
	Text_in_ui_.setStyle(Text_style_);
	Text_in_ui_.setFillColor(Text_color_);

	Text_in_ui_.setRotation(this->CalculateGradus());
	Text_in_ui_.setPosition(this->GetCoordinateCentre());
	
	if (text_centre_ == 0) {
		Text_in_ui_.setOrigin(sf::Vector2f(//centre
			this->GetOffsetSprite().x - (this->GetWidthSprite(true) / 2 -
				Text_in_ui_.getLocalBounds().width / 2),
			this->GetOffsetSprite().y - ((this->GetHeightSprite(true) / 2.0f -
				(int)character_size_ * 0.70f))));
	}
	else if (text_centre_ < 0) {
		Text_in_ui_.setOrigin(sf::Vector2f(//left
			this->GetOffsetSprite().x - cursor_size_ + text_centre_,
			this->GetOffsetSprite().y - ((this->GetHeightSprite(true) / 2.0f -
				(int)character_size_ * 0.70f))));
	}
	else {
		Text_in_ui_.setOrigin(sf::Vector2f(//right
			this->GetOffsetSprite().x - (this->GetWidthSprite(true) -
				Text_in_ui_.getLocalBounds().width) + cursor_size_ + text_centre_,
			this->GetOffsetSprite().y - ((this->GetHeightSprite(true) / 2.0f -
				(int)character_size_ * 0.70f))));
	}
	window.draw(Text_in_ui_);

	//draw cursor:
	if (time_blink_cursor_ < 500 && show_cursor_) {
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(cursor_size_, 
			(float)Text_in_ui_.getCharacterSize()));
		rectangle.setFillColor(Text_color_);

		rectangle.setRotation(this->CalculateGradus());
		rectangle.setPosition(this->GetCoordinateCentre());
		
		if (text_centre_ == 0) {
			rectangle.setOrigin(sf::Vector2f(//centre
				this->GetOffsetSprite().x - (this->GetWidthSprite(true) / 2) -
				(Text_in_ui_.getLocalBounds().width / 2) - rectangle.getLocalBounds().width,
				this->GetOffsetSprite().y - ((this->GetHeightSprite(true) -
					rectangle.getLocalBounds().height) / 2)));
		}
		else if (text_centre_ < 0) {
			rectangle.setOrigin(sf::Vector2f(//left
				this->GetOffsetSprite().x - Text_in_ui_.getLocalBounds().width -
				rectangle.getLocalBounds().width + text_centre_,
				this->GetOffsetSprite().y - ((this->GetHeightSprite(true) -
					rectangle.getLocalBounds().height) / 2)));
		}
		else {
			rectangle.setOrigin(sf::Vector2f(//right
				this->GetOffsetSprite().x - (this->GetWidthSprite(true))
					+ cursor_size_ + text_centre_,
				this->GetOffsetSprite().y - ((this->GetHeightSprite(true) -
					rectangle.getLocalBounds().height) / 2)));
		}
		window.draw(rectangle);
	}
}
