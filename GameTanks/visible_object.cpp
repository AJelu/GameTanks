#include "objects.h"
VisibleObject::VisibleObject() : AudioObject() 
{

}

VisibleObject::VisibleObject(int id_object,
	sf::Vector2f coordinate_centre,
	sf::Vector2f offset_sprite_coordinate,
	string texture, int frame_size_x, int frame_size_y) : AudioObject(id_object)
{
	SetCoordinate(coordinate_centre);
	SetOffsetSprite(offset_sprite_coordinate);
	SetTexture(texture, frame_size_x, frame_size_y);
}

void VisibleObject::SetNeedRedrawImage() { need_redraw_image_ = true; }

void VisibleObject::SetTile(int tile_level, int tile_number)
{
	//
}

void VisibleObject::StartPlayAnimate(int tile_level, int frame_start, int frame_end, bool looped)
{
	tile_level_ = tile_level;
	frame_start_ = frame_start;
	frame_end_ = frame_end;
	looped_ = looped;
}
bool VisibleObject::AnimateEnd()
{
	return false;
}
void VisibleObject::ForAnimate(float& game_time) //counting current frame
{

}

//get object parameters
bool VisibleObject::GetNeedRedrawImage() { return need_redraw_image_; };

sf::Vector2f VisibleObject::GetCoordinateCentre()
{ return Sprite_object_.getPosition(); }

int VisibleObject::GetHeight()
{ return Sprite_object_.getTextureRect().height; }

int VisibleObject::GetWidth()
{ return Sprite_object_.getTextureRect().width; }

sf::Vector2f VisibleObject::GetOffsetSprite()
{ return offset_sprite_coordinate_; }

//set object parameters
void VisibleObject::SetCoordinate(sf::Vector2f coordinate_centre)
{
	Sprite_object_.setPosition(coordinate_centre);
	SetNeedRedrawImage();
}

void VisibleObject::SetRotation(float rotation_by_gradus)
{
	Sprite_object_.setRotation(rotation_by_gradus);
	SetNeedRedrawImage();
}
;
void VisibleObject::SetTexture(string texture, int frame_size_x, int frame_size_y)
{
	frame_size_x_ = frame_size_x;
	frame_size_y_ = frame_size_y;
	////// texture create and other
	SetTile(0, 0);
	SetNeedRedrawImage();
}
void VisibleObject::SetOffsetSprite(sf::Vector2f offset_sprite_coordinate)
{
	offset_sprite_coordinate_ = offset_sprite_coordinate;
	Sprite_object_.setOrigin(offset_sprite_coordinate_);
	SetNeedRedrawImage();
}

void VisibleObject::Draw(sf::RenderWindow& window, View& Player_camera, bool plus_offset_camera)
{
	///
	need_redraw_image_ = false;
}