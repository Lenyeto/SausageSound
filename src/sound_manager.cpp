#include "stdafx.h"
#include <sound_manager.h>


template<> ssuge::SoundManager * ssuge::Singleton<ssuge::SoundManager>::msSingleton = nullptr;


ssuge::SoundManager::SoundManager()
{
	mSoundEngine = irrklang::createIrrKlangDevice();


}

ssuge::SoundManager::~SoundManager()
{
	mSoundEngine->drop();
}

irrklang::ISoundEngine * ssuge::SoundManager::getEngine()
{
	return mSoundEngine;
}