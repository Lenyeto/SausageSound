#ifndef _PHYSICS_MANAGER_H_
#define _PHYSICS_MANAGER_H_

#include "btBulletDynamicsCommon.h"
#include <stdafx.h>
#include <singleton.h>

#define PHYSICS_MANAGER ssuge::PhysicsManager::getSingletonPtr()





namespace ssuge
{

	/// The manager of all GameObjects.  All GameObjects are broken down into 
	/// named groups.  Each group can be batch destroyed / hid / etc.
	class PhysicsManager : public Singleton<PhysicsManager>
	{
	protected:
		btDiscreteDynamicsWorld* mDynamicsWorld;


	public:
		PhysicsManager();
		~PhysicsManager();


	public:
		void setGravity(btVector3 * force);
		void update(float deltaTime);
		void addRigidBody(btRigidBody * body);
		void removeRigidBody(btRigidBody * body);

	public:
		btVector3 toBulletVector(Ogre::Vector3 * v);
		Ogre::Vector3 toOgreVector(btVector3 * v);
	};

}










#endif