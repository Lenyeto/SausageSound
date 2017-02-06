#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include <stdafx.h>
#include <singleton.h>
#include <irrKlang.h>

#define SOUND_MANAGER ssuge::SoundManager::getSingletonPtr()

namespace ssuge
{
	class SoundManager : public Singleton<SoundManager>
	{
	// *** MEMBER VARIABLES *** //
	protected:
		//irrklang::ISoundSource sounds
		std::map<std::string, irrklang::ISound> mSounds;
		irrklang::ISoundEngine * mSoundEngine;
	// *** CONSTRUCTORS *** //
	public:
		SoundManager();
		~SoundManager();
	// *** METHODS *** //
	public:
		irrklang::ISoundEngine * getEngine();
	};
}



#endif