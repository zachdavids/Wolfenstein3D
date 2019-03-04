#ifndef AUDIO_H
#define AUDIO_H

#include <SFML\Audio.hpp>

class Audio
{
public:

	Audio();

	void PlayStep();
	void PlayPlayerGunshot();
	void PlayPlayerDeath();
	void PlayEnemyGunshot();
	void PlayEnemyDeath();
	void PlayMedkit();
	void PlayDoorOpen();
	void PlayDoorClose();
	void PlayLevelEnd();

private:

	sf::SoundBuffer buffer_;
	sf::Sound sound_;
};

#endif;