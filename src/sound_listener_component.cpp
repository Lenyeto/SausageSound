#include "stdafx.h"


#include <game_object.h>
#include <sound_listener_component.h>
#include <sound_manager.h>


ssuge::SoundListenerComponent::SoundListenerComponent(GameObject * p) : ssuge::Component(p)
{

}

void ssuge::SoundListenerComponent::update(float dt)
{
//	SOUND_MANAGER->getEngine()->setListenerPosition(irrklang::vec3df(mOwner->getPosition().x, mOwner->getPosition().y, mOwner->getPosition().z), irrklang::vec3df(mOwner->getOrientation().getPitch().valueRadians, mOwner->getOrientation().getRoll().valueRadians, mOwner->getOrientation().getYaw().valueRadians));
}

ssuge::SoundListenerComponent::~SoundListenerComponent()
{

}