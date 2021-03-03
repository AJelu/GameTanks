#include <iostream>
#include "objects.h"

AudioObject::AudioObject() : BaseObject() { }
AudioObject::AudioObject(int const& id_object) : BaseObject(id_object) { }

void AudioObject::AddAudioAction(string const& audio_action,
									string const& audio_file, int const& volume)
{
	if (!audio_action.empty() && !audio_file.empty()) {
		audio_action_name_.push_back(audio_action);

		SoundBuffer* sound_buffer = new SoundBuffer();
		(*sound_buffer).loadFromFile(audio_file);
		sounds_buffer_.push_back(sound_buffer);

		Sound* sound = new Sound();
		(*sound).setBuffer(*sound_buffer);
		sounds_file_.push_back(sound);

		sounds_volume_.push_back(volume);

		sound_buffer = nullptr;
		sound = nullptr;
	}	
	else std::cout << "Variables: audio_action or audio_file is empty!" << std::endl;
}

bool AudioObject::StartAudioAction(string const& audio_action, bool looped)
{
	for (int i = 0; i < audio_action_name_.size(); i++) {
		if (audio_action_name_[i] == audio_action) {
			(*sounds_file_[i]).play();
			(*sounds_file_[i]).setLoop(looped);
			return true;
		}
	}
	return false;
}

bool AudioObject::StopAudioAction(string const& audio_action)
{
	for (int i = 0; i < audio_action_name_.size(); i++) {
		if (audio_action_name_[i] == audio_action) {
			(*sounds_file_[i]).setLoop(false);
			(*sounds_file_[i]).stop();
			return true;
		}
	}
	return false;
}

AudioObject::~AudioObject()
{
	for (int i = 0; i < audio_action_name_.size(); i++) {
		if (sounds_file_.at(i)) delete sounds_file_[i]; //test mode of access verification
		if (sounds_buffer_.at(i)) delete sounds_buffer_[i]; //test mode of access verification
	}
}