#include <stdafx.h>
#include <physics_component.h>
#include <game_object.h>
#include <physics_manager.h>
#include <application.h>

ssuge::PhysicsComponent::PhysicsComponent(GameObject * p, const char * s, float mass, bool isBulletControlled) : ssuge::Component::Component(p)
{
	btMotionState * motionState = new btDefaultMotionState();

	btCollisionShape * shape;

	if (s == "box")
	{
		shape = new btBoxShape(btVector3(mGameObject->getSceneNode()->getScale().x, mGameObject->getSceneNode()->getScale().y, mGameObject->getSceneNode()->getScale().z));
		mRigidBody = new btRigidBody(btScalar(mass), motionState, shape);
	}
	else if (s == "sphere")
	{
		shape = new btSphereShape(btScalar(mGameObject->getSceneNode()->getScale().x));
		mRigidBody = new btRigidBody(btScalar(mass), motionState, shape);
	}
	else {
		LOG_MANAGER->log("Error, tried to assign a null shape to a physics componenet");
		APPLICATION->quit();
	}


	isAffectedByBullet = isBulletControlled;

	PHYSICS_MANAGER->addRigidBody(mRigidBody);

	mGameObject = p;
}

ssuge::PhysicsComponent::~PhysicsComponent()
{
	PHYSICS_MANAGER->removeRigidBody(mRigidBody);
}

void ssuge::PhysicsComponent::update(float dt)
{
	mGameObject->setPosition(PHYSICS_MANAGER->toOgreVector(&mRigidBody->getWorldTransform().getOrigin()));
}
