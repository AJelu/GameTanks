#include "objects.h"

AudioObject::AudioObject() : BaseObject() { }
AudioObject::AudioObject(int id_object) : BaseObject(id_object) { }

void AudioObject::AddAudioAction(string audio_action, string audio_file, int volume)
{
	audio_action_name_.push_back(audio_action);
	sf::Sound* sound = new sf::Sound();
	/// <--------------------------------------------------
	sounds_file_.push_back(sound);
	sf::SoundBuffer* sound_buffer = new sf::SoundBuffer();
	/// <--------------------------------------------------
	sounds_buffer_.push_back(sound_buffer);
	sounds_volume_.push_back(volume);
}

bool AudioObject::StartAudioAction(string audio_action, bool looped)
{
	for (int i = 0; i < audio_action_name_.size(); i++){
		if (audio_action_name_[i] == audio_action) {
			//play sound <---------------------------------------------------
		}
	}
}

bool AudioObject::StopAudioAction(string audio_action)
{
	for (int i = 0; i < audio_action_name_.size(); i++) {
		if (audio_action_name_[i] == audio_action) {
			//stop play sound <---------------------------------------------------
		}
	}
}

AudioObject::~AudioObject()
{
	for (int i = 0; i < audio_action_name_.size(); i++) {
		delete sounds_file_[i];
		delete sounds_buffer_[i];
	}
}