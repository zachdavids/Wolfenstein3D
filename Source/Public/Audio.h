#pragma once

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

	//sf::Sound m_Sound;
	//sf::SoundBuffer m_Buffer;
	//const std::string m_Path = "Resources/Sounds/";
};