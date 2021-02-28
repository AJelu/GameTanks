#include "objects.h"

AudioObject::AudioObject() : BaseObject()
{

}

AudioObject::AudioObject(int id_object) : BaseObject(id_object) 
{

}

void AudioObject::AddAudioAction(string audio_action, string audio_file, int volume)
{

}

bool AudioObject::StartAudioAction(string audio_action, bool looped)
{
	return false;
}

bool AudioObject::StopAudioAction(string audio_action)
{
	return false;
}

AudioObject::~AudioObject()
{
	//delete vectors
}