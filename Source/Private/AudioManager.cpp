#include "AudioManager.h"

AudioManager* AudioManager::m_Instance;

void AudioManager::Create()
{
	if (m_Instance) { return; }
	m_Instance = this;

	m_SoundEngine = irrklang::createIrrKlangDevice();
}

void AudioManager::Destroy()
{
	m_Music->drop();
	m_SoundEngine->drop();
}

void AudioManager::PlayMusic()
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/GetThemBeforeTheyGetYou.ogg"))
	{
		m_Music = m_SoundEngine->play2D(
			"Resources/Sounds/GetThemBeforeTheyGetYou.ogg",
			true,
			false,
			true
		);
		m_Music->setVolume(0.10f);
	}
}

void AudioManager::PlayPistol(glm::vec3 const& position)
{
	m_SoundEngine->play3D(
		"Resources/Sounds/Pistol.wav",
		irrklang::vec3df(position.x, 0, position.z)
	);
}

void AudioManager::PlayMachineGun(glm::vec3 const& position)
{
	m_SoundEngine->play3D(
		"Resources/Sounds/MachineGun.wav",
		irrklang::vec3df(position.x, 0, position.z)
	);
}

void AudioManager::PlayMinigun(glm::vec3 const& position)
{
	m_SoundEngine->play3D(
		"Resources/Sounds/Minigun.wav",
		irrklang::vec3df(position.x, 0, position.z)
	);
}

void AudioManager::PlayKnife(glm::vec3 const& position)
{
	m_SoundEngine->play3D(
		"Resources/Sounds/Knife.wav",
		irrklang::vec3df(position.x, 0, position.z)
	);
}

void AudioManager::PlayPlayerDeath(glm::vec3 const& position)
{
	//if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/PlayerDeath.wav"))
	//{
	//	m_SoundEngine->play3D(
	//		"Resources/Sounds/PlayerDeath.wav",
	//		irrklang::vec3df(0.0f, -0.25f, 0.0f)
	//	);
	//}
}

void AudioManager::PlayMedkit(glm::vec3 const& position)
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/Food.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/Food.wav",
			irrklang::vec3df(position.x, 0, position.z)
		);
	}
}

void AudioManager::PlayEnemyDeath(glm::vec3 const& position)
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/EnemyDeath.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/EnemyDeath.wav",
			irrklang::vec3df(position.x, 0, position.z)
		);
	}
}

void AudioManager::PlayAmmoPickup(glm::vec3 const& position)
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/Ammo.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/Ammo.wav",
			irrklang::vec3df(position.x, 0, position.z)
		);
	}
}

void AudioManager::PlayDoor(glm::vec3 const& position)
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/Door.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/Door.wav",
			irrklang::vec3df(position.x, 0, position.z)
		);
	}
}

void AudioManager::PlayLevelEnd()
{
	//if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/LevelEnd.wav"))
	//{
	//	m_SoundEngine->play3D(
	//		"Resources/Sounds/LevelEnd.wav",
	//		irrklang::vec3df(0.0f, -0.25f, 0.0f)
	//	);
	//}
}

void AudioManager::SetListenerPosition(glm::vec3 const& position, glm::vec3 const& direction)
{
	m_SoundEngine->setListenerPosition(
		irrklang::vec3df(position.x, 0, position.z),
		irrklang::vec3df(direction.x, direction.y, direction.z)
	);
}
