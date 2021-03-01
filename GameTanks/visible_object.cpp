#define _USE_MATH_DEFINES
#include <cmath>
#include "objects.h"

VisibleObject::VisibleObject() : AudioObject() 
{
	SetCoordinate(sf::Vector2f(0.0f, 0.0f));
	SetOffsetSprite(sf::Vector2f(0.0f, 0.0f));
	SetTexture("", 0, 0);
}

VisibleObject::VisibleObject(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	string const& texture, int const& frame_count_x, 
	int const& frame_count_y) : AudioObject(id_object)
{
	SetCoordinate(coordinate_centre);
	SetOffsetSprite(offset_sprite_coordinate);
	SetTexture(texture, frame_count_x, frame_count_y);
}

void VisibleObject::SetNeedRedrawImage() 
{ need_redraw_image_ = true; }

bool VisibleObject::RecalculateVector() //rotate vector be lengh 1
{
	float length_vector = 
		  vector_rotate_x_ * vector_rotate_x_ 
		+ vector_rotate_y_ * vector_rotate_y_;
	if (length_vector == 0.0f){ return false; } //exit if error

	length_vector = sqrtf(length_vector);
	vector_rotate_x_ /= vector_rotate_x_;
	vector_rotate_y_ /= vector_rotate_y_;
	return true;
}

//just showing current tile 
bool VisibleObject::ShowTile()
{
	int x1, y1, x2, y2;
	x1 = this->GetWidthSprite() * (tile_frame_current_ - 1);
	x2 = this->GetWidthSprite() * (tile_frame_current_) - 1;

	y1 = this->GetHeightSprite() * (tile_level_ - 1);
	y2 = this->GetHeightSprite() * (tile_level_) - 1;

	Sprite_object_.setTextureRect(IntRect(x1, y1, x2, y2));

	return true;
}

//set position (choosed frame texture) and show choosed frame; return true if chenge position
bool VisibleObject::SetTile(int const& tile_level, int const& tile_number)
{
	if (tile_level > frame_count_y_ || tile_level < 1) { return false; }
	if (tile_number > frame_count_x_ || tile_number < 1) { return false; }
	if (tile_level == tile_level_ && tile_number == tile_frame_current_) { return false; }
	tile_level_ = tile_level;
	tile_frame_current_ = tile_number;
	ShowTile();
	SetNeedRedrawImage();
	return true;
}

void VisibleObject::StartPlayAnimation(int const& tile_level,
	int const& frame_start, int const& frame_end,
	float const& animation_speed_for_frame, bool const& looped)
{
	//check is no out of range and write new parameter for animate
	if (tile_level > frame_count_y_) { tile_level_ = frame_count_y_; }
	else if (tile_level < 1) { tile_level_ = 1; }
	else { tile_level_ = tile_level; }

	if (frame_start > frame_count_x_) { animation_frame_start_ = frame_count_x_; }
	else if (frame_start < 1) { animation_frame_start_ = 1; }
	else { animation_frame_start_ = frame_start; }

	if (frame_end > frame_count_x_) { animation_frame_end_ = frame_count_x_; }
	else if (frame_end < 1) { animation_frame_end_ = 1; }
	else { animation_frame_end_ = frame_end; }

	animation_speed_for_frame_ = animation_speed_for_frame;
	looped_ = looped and (frame_start != frame_end);

	//set start parameters
	current_frame_animation_time_ = 0;
	SetTile(tile_level_, animation_frame_start_);
}

bool VisibleObject::AnimationEnd()
{
	if (tile_frame_current_ == animation_frame_end_) { return true; }
	return false;
}

void VisibleObject::ForAnimation(float const& game_time) //counting current frame
{
	if (animation_frame_end_ != animation_frame_start_) {
		current_frame_animation_time_ += game_time; // add time "one screen frame"
		while (current_frame_animation_time_ > animation_speed_for_frame_) {
			current_frame_animation_time_ -= animation_speed_for_frame_;

			if (!AnimationEnd()) {
				SetTile(tile_level_, tile_frame_current_ +
					((animation_frame_end_ > animation_frame_start_) ? 1 : -1));
			}
			else if (looped_) {
				SetTile(tile_level_, animation_frame_start_);
			}
		}
	}
}

//get object parameters
bool VisibleObject::GetNeedRedrawImage() 
{ return need_redraw_image_; };

sf::Vector2f VisibleObject::GetCoordinateCentre()
{ return Sprite_object_.getPosition(); }

int VisibleObject::GetHeightSprite()
{ return Texture_object_.getSize().y / frame_count_y_; }

int VisibleObject::GetWidthSprite()
{ return Texture_object_.getSize().x / frame_count_x_; }

float VisibleObject::GetVectorX()
{ return vector_rotate_x_; }

float VisibleObject::GetVectorY()
{ return vector_rotate_y_; }

sf::Vector2f VisibleObject::GetOffsetSprite()
{ return offset_sprite_coordinate_; }

//set object parameters
void VisibleObject::SetCoordinate(sf::Vector2f const& coordinate_centre)
{
	Sprite_object_.setPosition(coordinate_centre);
	SetNeedRedrawImage();
}

void VisibleObject::SetRotationVector(float const& vector_x, float const& vector_y)
{
	vector_rotate_x_ = vector_x;
	vector_rotate_y_ = vector_y;
	RecalculateVector();

	float temp_vector_x = 0.0f;//create and set temp vector
	float temp_vector_y = 1.0f;
	float rotation_by_gradus = 
		acosf((temp_vector_x * vector_x + temp_vector_y * vector_y) /
		(sqrtf(temp_vector_x * temp_vector_x + temp_vector_y * temp_vector_y) *
			sqrtf(vector_x * vector_x + vector_y * vector_y)));
	rotation_by_gradus = (rotation_by_gradus * 180) / M_PI; //calculate temp gradus

	temp_vector_x = 1.0f;//set temp vector
	temp_vector_y = 0.0f;
	float rotation_by_gradus_buffer = 
		acosf((temp_vector_x * vector_x + temp_vector_y * vector_y) /
		(sqrtf(temp_vector_x * temp_vector_x + temp_vector_y * temp_vector_y) *
			sqrtf(vector_x * vector_x + vector_y * vector_y)));
	rotation_by_gradus_buffer = (rotation_by_gradus_buffer * 180) / M_PI;//calculate temp gradus

	if (rotation_by_gradus_buffer > 90.0f) { //calculete new gradus
		rotation_by_gradus = 360 - rotation_by_gradus;
	}

	Sprite_object_.setRotation(rotation_by_gradus);
	SetNeedRedrawImage();
}

void VisibleObject::RotationVector(int const& rotation_degree)
{
	float new_vector_x, new_vector_y;
	float to_radian = rotation_degree * M_PI / 180.0f;
	new_vector_x = vector_rotate_x_ * cos(to_radian) + 
					vector_rotate_y_ * sin(to_radian);
	new_vector_y = vector_rotate_x_ * sin(to_radian) + 
					vector_rotate_y_ * cos(to_radian);
	SetRotationVector (new_vector_x, new_vector_y);
}

void VisibleObject::SetRotation(float const& rotation_by_gradus)
{
	vector_rotate_x_ = 0.0f;
	vector_rotate_y_ = 1.0f;
	RotationVector(rotation_by_gradus);
}
;
void VisibleObject::SetTexture(string const& texture, 
							int const& frame_count_x, int const& frame_count_y)
{
	frame_count_x_ = frame_count_x;
	frame_count_y_ = frame_count_y;
	Texture_object_.loadFromFile(texture);
	Sprite_object_.setTexture(Texture_object_);
	Sprite_object_.setTextureRect( IntRect(0, 0, GetWidthSprite(), GetHeightSprite()));
	SetTile(1, 1);
	SetOffsetSprite(offset_sprite_coordinate_);
	SetNeedRedrawImage();
}
void VisibleObject::SetOffsetSprite(sf::Vector2f const& offset_sprite_coordinate)
{
	offset_sprite_coordinate_ = offset_sprite_coordinate;
	Sprite_object_.setOrigin(offset_sprite_coordinate_);
	SetNeedRedrawImage();
}

void VisibleObject::Draw(sf::RenderWindow& window, 
					View const& Player_camera, bool const& plus_offset_camera)
{
	if (plus_offset_camera) {
		// +offset camera????????? <----------------------------------------------
		window.draw(Sprite_object_);
	}
	else {
		window.draw(Sprite_object_);
	}
	need_redraw_image_ = false;
}