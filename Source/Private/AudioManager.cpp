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
	m_Music = m_SoundEngine->play2D(
		"Resources/Sounds/GetThemBeforeTheyGetYou.ogg",
		true,
		false,
		true
	);
	m_Music->setVolume(0.10f);
}

void AudioManager::PlayPistol(glm::vec3 const& position)
{
	m_SoundEngine->play3D(
		"Resources/Sounds/Pistol.wav",
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

void AudioManager::PlayMedkit()
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/Health.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/Health.wav",
			irrklang::vec3df(0.0f, -0.25f, 0.0f)
		);
	}
}

void AudioManager::PlayEnemyDeath(glm::vec3 const& position)
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/EnemyDeath1.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/EnemyDeath1.wav",
			irrklang::vec3df(position.x, 0, position.z)
		);
	}
}

void AudioManager::PlayDoorOpen()
{
	//if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/DoorOpen.wav"))
	//{
	//	m_SoundEngine->play3D(
	//		"Resources/Sounds/DoorOpen.wav",
	//		irrklang::vec3df(0.0f, -0.25f, 0.0f)
	//	);
	//}
}

void AudioManager::PlayDoorClose()
{
	//if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/DoorClose.wav"))
	//{
	//	m_SoundEngine->play3D(
	//		"Resources/Sounds/DoorClose.wav",
	//		irrklang::vec3df(0.0f, -0.25f, 0.0f)
	//	);
	//}
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
