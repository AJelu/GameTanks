#include <iostream>
#include "objects.h"

std::vector<std::string> AudioObject::Audio_file_name_;
std::vector<sf::SoundBuffer*> AudioObject::Sounds_buffer_;

sf::SoundBuffer* AudioObject::GetSoundsBuffer(std::string audio_file) {

	for (int i = 0; i < (int)Audio_file_name_.size(); i++) {
		if (Audio_file_name_[i] == audio_file) { return Sounds_buffer_[i]; }
	}
	sf::SoundBuffer* Sound_buffer = new sf::SoundBuffer();
	if (Sound_buffer->loadFromFile(audio_file)) {
		Audio_file_name_.push_back(audio_file);
		Sounds_buffer_.push_back(Sound_buffer);
		return Sounds_buffer_.back();
	}
	delete Sound_buffer;
	return nullptr;
}

bool AudioObject::PlayAudioAction(std::string const& audio_action, bool looped) {
	bool result = false;
	for (int i = 0; i < (int)Audio_action_name_.size(); i++) {
		if (Audio_action_name_[i] == audio_action) {
			bool need_play_sound = true;
			for (int j = 0; j < (int)Audio_action_playing_name_.size(); j++)
				if (Audio_action_name_[i] == Audio_action_playing_name_[j]) {
					need_play_sound = false;
					break;
				}
			if (need_play_sound) {
				sf::SoundBuffer* sound_buffer =
					this->GetSoundsBuffer(Audio_action_file_name_[i]);
				sf::Sound* sound = new sf::Sound();
				sound->setBuffer(*sound_buffer);
				sound->setVolume(Audio_action_volume[i]);
				Audio_action_playing_name_.push_back(audio_action);
				Sounds_file_.push_back(sound);
				Sounds_file_.back()->setLoop(looped);
				Sounds_file_.back()->play();
				result = true;
			}
		}
	}
	return result;
}

bool AudioObject::StopPlayingAudioAction(std::string const& audio_action) {
	bool result = false;
	for (int i = 0; i < (int)Audio_action_playing_name_.size(); i++) {
		if (Audio_action_playing_name_[i] == audio_action || 
			(Sounds_file_[i]->getStatus() != sf::Sound::Status::Playing)) {
			Sounds_file_[i]->setLoop(false);
			Sounds_file_[i]->stop();
			delete Sounds_file_[i];
			Sounds_file_.erase(Sounds_file_.begin() + i);
			Audio_action_playing_name_.erase(Audio_action_playing_name_.begin() + i);
			i--;
			result = true;
		}
	}
	return result;
}

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
									std::string const& audio_file, float const& volume){
	Audio_action_name_.push_back(audio_action_name);
	Audio_action_file_name_.push_back(audio_file);
	Audio_action_volume.push_back(volume);
}

bool AudioObject::StartAudioAction(std::string const& audio_action, bool looped){
	Start_audio_action_.push(audio_action);
	Start_looped_.push(looped);
	return true;
}

bool AudioObject::StopAudioAction(std::string const& audio_action){
	Stop_audio_action_.push(audio_action);
	return true;
}

bool AudioObject::PlaysSounds() {
	return Sounds_file_.size() > 0;
}

void AudioObject::SetCamera(sf::View* Camera) { Camera_ = Camera; }

sf::View* AudioObject::GetCamera() { return Camera_; }

void AudioObject::RecalculateState(float const& game_time) {
	VisibleObject::RecalculateState(game_time);

	bool in_range = false;
	if ((Camera_ != nullptr)) {
		if (((Camera_->getCenter().x - Camera_->getSize().x / 2)
				< this->GetCoordinateCentre().x) && 
			((Camera_->getCenter().x + Camera_->getSize().x / 2)
				> this->GetCoordinateCentre().x) &&
			((Camera_->getCenter().y - Camera_->getSize().y / 2)
				< this->GetCoordinateCentre().y) &&
			((Camera_->getCenter().y + Camera_->getSize().y / 2)
				> this->GetCoordinateCentre().y))
			in_range = true;
	}
	while (!Start_audio_action_.empty()) {
		if (in_range)
			this->PlayAudioAction(Start_audio_action_.front(), Start_looped_.front());
		Start_audio_action_.pop();
		Start_looped_.pop();
	}
	this->StopPlayingAudioAction(""); //for deleting ended sound objects
	while (!Stop_audio_action_.empty()) {
		this->StopPlayingAudioAction(Stop_audio_action_.front());
		Stop_audio_action_.pop();
	}
}

std::string AudioObject::ClassName() { return "AudioObject"; }

bool AudioObject::CreatePacket(sf::Packet& Packet) {
	VisibleObject::CreatePacket(Packet);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="Packet"></param>
	/// <returns></returns>
	return false;
}

bool AudioObject::SetDataFromPacket(sf::Packet& Packet) {
	VisibleObject::SetDataFromPacket(Packet);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="Packet"></param>
	/// <returns></returns>
	return false;
}

AudioObject::~AudioObject(){
	for (int i = 0; i < (int)Sounds_file_.size(); i++) {
		if (Sounds_file_.at(i)) delete Sounds_file_[i]; //test mode of access verification
	}
}