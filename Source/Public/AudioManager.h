#pragma once

#include <GLM/vec3.hpp>
#include <irrklang/irrKlang.h>

class AudioManager
{
public:

	AudioManager() = default;
	void Create();
	void Destroy();
	void PlayMusic();
	void PlayKnife(glm::vec3 const& position);
	void PlayPistol(glm::vec3 const& position);
	void PlayMachineGun(glm::vec3 const& position);
	void PlayMinigun(glm::vec3 const& position);
	void PlayPlayerDeath(glm::vec3 const& position);
	void PlayEnemyDeath(glm::vec3 const& position);
	void PlayAmmoPickup(glm::vec3 const& position);
	void PlayMedkit();
	void PlayDoorOpen();
	void PlayDoorClose();
	void PlayLevelEnd();
	void SetListenerPosition(glm::vec3 const& position, glm::vec3 const& rotation);
	static AudioManager* Get() { return m_Instance; }

private:

	static AudioManager* m_Instance;
	irrklang::ISound* m_Music = nullptr;
	irrklang::ISoundEngine* m_SoundEngine = nullptr;
};