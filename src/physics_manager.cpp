#include "stdafx.h"
#include "physics_manager.h"

template<> ssuge::PhysicsManager * ssuge::Singleton<ssuge::PhysicsManager>::msSingleton = nullptr;


ssuge::PhysicsManager::PhysicsManager()
{
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	mDynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
}

ssuge::PhysicsManager::~PhysicsManager()
{
	delete mDynamicsWorld;
}

void ssuge::PhysicsManager::setGravity(btVector3 * force)
{
	mDynamicsWorld->setGravity(*force);
}

btVector3 ssuge::PhysicsManager::toBulletVector(Ogre::Vector3 * v)
{
	return btVector3(v->x, v->y, v->z);
}

Ogre::Vector3 ssuge::PhysicsManager::toOgreVector(btVector3 * v)
{
	
	return Ogre::Vector3(v->getX(), v->getY(), v->getZ());

}

void ssuge::PhysicsManager::update(float deltaTime)
{
	mDynamicsWorld->stepSimulation(1.f / 60.f, 10);

	/*
	//print positions of all objects
	for (int j = mDynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject* obj = mDynamicsWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);

		}
		else
		{
			trans = obj->getWorldTransform();
		}
		//printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}
	*/
}

void ssuge::PhysicsManager::addRigidBody(btRigidBody * body)
{
	mDynamicsWorld->addRigidBody(body);
}

void ssuge::PhysicsManager::removeRigidBody(btRigidBody * body)
{
	mDynamicsWorld->removeRigidBody(body);
}