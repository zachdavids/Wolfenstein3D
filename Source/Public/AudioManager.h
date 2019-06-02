#pragma once

#include <irrklang/irrKlang.h>

class AudioManager
{
public:

	AudioManager() = default;
	void Create();
	void Destroy();
	void PlayMusic();
	void PlayStep();
	void PlayPlayerGunshot();
	void PlayPlayerDeath();
	void PlayEnemyGunshot();
	void PlayEnemyDeath();
	void PlayMedkit();
	void PlayDoorOpen();
	void PlayDoorClose();
	void PlayLevelEnd();
	static AudioManager* Get() { return m_Instance; }

private:

	static AudioManager* m_Instance;
	irrklang::ISound* m_Music = nullptr;
	irrklang::ISoundEngine* m_SoundEngine = nullptr;
};