#include "stdafx.h"
#include <game_object.h>
#include <sound_component.h>
#include <sound_manager.h>


ssuge::SoundComponent::SoundComponent(GameObject * p, std::string fname) : ssuge::Component(p)
{
	//															position,				isLooped, startPaused, Track
	mSound = SOUND_MANAGER->getEngine()->play3D(fname.c_str(), irrklang::vec3df(0, 0, 0), true, false, false);

}

void ssuge::SoundComponent::update(float dt)
{
	
	mSound->setPosition(irrklang::vec3df(mOwner->getPosition().x, mOwner->getPosition().y, mOwner->getPosition().z));
}

void ssuge::SoundComponent::play()
{

}