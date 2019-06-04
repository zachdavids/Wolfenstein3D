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

void AudioManager::PlayStep()
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/Step.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/Step.wav",
			irrklang::vec3df(0.0f, -0.25f, 0.0f)
		);
	}
}

void AudioManager::PlayPlayerGunshot()
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/PlayerGunshot.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/PlayerGunshot.wav",
			irrklang::vec3df(0.0f, -0.25f, 0.0f)
		);
	}
}

void AudioManager::PlayPlayerDeath()
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/PlayerDeath.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/PlayerDeath.wav",
			irrklang::vec3df(0.0f, -0.25f, 0.0f)
		);
	}
}

void AudioManager::PlayEnemyGunshot()
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/EnemyGunshot.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/EnemyGunshot.wav",
			irrklang::vec3df(0.0f, -0.25f, 0.0f)
		);
	}
}

void AudioManager::PlayMedkit()
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/Medkit.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/Medkit.wav",
			irrklang::vec3df(0.0f, -0.25f, 0.0f)
		);
	}
}

void AudioManager::PlayEnemyDeath()
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/EnemyDeath.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/EnemyDeath.wav",
			irrklang::vec3df(0.0f, -0.25f, 0.0f)
		);
	}
}

void AudioManager::PlayDoorOpen()
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/DoorOpen.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/DoorOpen.wav",
			irrklang::vec3df(0.0f, -0.25f, 0.0f)
		);
	}
}

void AudioManager::PlayDoorClose()
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/DoorClose.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/DoorClose.wav",
			irrklang::vec3df(0.0f, -0.25f, 0.0f)
		);
	}
}

void AudioManager::PlayLevelEnd()
{
	if (!m_SoundEngine->isCurrentlyPlaying("Resources/Sounds/LevelEnd.wav"))
	{
		m_SoundEngine->play3D(
			"Resources/Sounds/LevelEnd.wav",
			irrklang::vec3df(0.0f, -0.25f, 0.0f)
		);
	}
}