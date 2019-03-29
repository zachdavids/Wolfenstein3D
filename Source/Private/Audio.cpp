#include "Audio.h"

Audio::Audio()
{
	sound_.setBuffer(buffer_);
	sound_.setVolume(30);
}

void Audio::PlayStep()
{
	if (sound_.getStatus() == sf::SoundSource::Stopped) {
		sound_.setVolume(20) ;
		buffer_.loadFromFile(path + "step.wav");
		sound_.play();
	}
}

void Audio::PlayPlayerGunshot()
{
	buffer_.loadFromFile(path + "gunshot.wav");
	sound_.setVolume(30);
	sound_.play();
}

void Audio::PlayPlayerDeath()
{
	buffer_.loadFromFile(path + "record6.wav");
	sound_.play();
}

void Audio::PlayEnemyGunshot()
{
	if (sound_.getStatus() == sf::SoundSource::Stopped) {
		buffer_.loadFromFile(path + "mp5.wav");
		sound_.setVolume(4);
		sound_.play();
	}
}

void Audio::PlayMedkit()
{
	buffer_.loadFromFile(path + "smw_power.wav");
	sound_.setVolume(70);
	sound_.play();
}

void Audio::PlayEnemyDeath()
{
	buffer_.loadFromFile(path + "record4.wav");
	sound_.play();
}

void Audio::PlayDoorOpen()
{
	if (sound_.getStatus() == sf::SoundSource::Stopped) {
		buffer_.loadFromFile(path + "dooropen.wav");
		sound_.play();
	}
}

void Audio::PlayDoorClose()
{
	if (sound_.getStatus() == sf::SoundSource::Stopped) {
		buffer_.loadFromFile(path + "doorclose.wav");
		sound_.play();
	}
}

void Audio::PlayLevelEnd()
{
	if (sound_.getStatus() == sf::SoundSource::Stopped) {
		sound_.setVolume(100);
		buffer_.loadFromFile(path + "smw.wav");
		sound_.play();
	}
}