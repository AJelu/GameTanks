#include <iostream>
#include "objects.h"

AudioObject::AudioObject() : VisibleObject() {
	Camera_ = nullptr;
}
AudioObject::AudioObject(int const& id_object,
	sf::Vector2f const& coordinate_centre,
	sf::Vector2f const& offset_sprite_coordinate,
	std::string const& texture, int const& frame_count_x, int const& frame_count_y) : 
	VisibleObject(id_object, coordinate_centre, offset_sprite_coordinate,
		texture, frame_count_x, frame_count_y) {
	Camera_ = nullptr;
}

void AudioObject::AddAudioAction(std::string const& audio_action_name,
									std::string const& audio_file, int const& volume){
	if (!audio_action_name.empty() && !audio_file.empty()) {
		audio_action_name_.push_back(audio_action_name);

		sf::SoundBuffer* sound_buffer = new sf::SoundBuffer();
		(*sound_buffer).loadFromFile(audio_file);
		sounds_buffer_.push_back(sound_buffer);

		sf::Sound* sound = new sf::Sound();
		(*sound).setBuffer(*sound_buffer);
		sounds_file_.push_back(sound);

		sounds_volume_.push_back(volume);

		sound_buffer = nullptr;
		sound = nullptr;
	}	
	else std::cout << "Variables: audio_action or audio_file is empty!" << std::endl;
}

bool AudioObject::StartAudioAction(std::string const& audio_action, bool looped){
	bool result = false;
	for (int i = 0; i < (int)audio_action_name_.size(); i++) {
		if (audio_action_name_[i] == audio_action) {
			(*sounds_file_[i]).play();
			(*sounds_file_[i]).setLoop(looped);
			result = true;
		}
	}
	return result;
}

bool AudioObject::StopAudioAction(std::string const& audio_action){
	for (int i = 0; i < (int)audio_action_name_.size(); i++) {
		if (audio_action_name_[i] == audio_action) {
			(*sounds_file_[i]).setLoop(false);
			(*sounds_file_[i]).stop();
			return true;
		}
	}
	return false;
}

void AudioObject::SetCamera(sf::View* Camera) { Camera_ = Camera; }

sf::View* AudioObject::GetCamera() { return Camera_; }

void AudioObject::RecalculateState(float const& game_time) {
	VisibleObject::RecalculateState(game_time);
}

AudioObject::~AudioObject(){
	for (int i = 0; i < (int)audio_action_name_.size(); i++) {
		if (sounds_file_.at(i)) delete sounds_file_[i]; //test mode of access verification
		if (sounds_buffer_.at(i)) delete sounds_buffer_[i]; //test mode of access verification
	}
}