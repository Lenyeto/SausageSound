#ifndef _PHYSICS_COMPONENT_FACTORY_H_
#define _PHYSICS_COMPONENT_FACTORY_H_

#include <stdafx.h>
#include <singleton.h>
#include <component_factory.h>

#define PHYSICS_COMPONENT_FACTORY ssuge::PhysicsComponentFactory::getSingletonPtr()

namespace ssuge
{
	class PhysicsComponent;

	/// The MeshComponentFactory is used to create instances of MeshComponents.
	class PhysicsComponentFactory : public ComponentFactory<PhysicsComponent>, public Singleton<PhysicsComponentFactory>
	{
		// @@@@@ CONSTRUCTORS / DESTRUCTORS @@@@@ //
	public:
		/// Creates the mesh component factory with the given number of "slots"
		PhysicsComponentFactory(unsigned int max_size) : ComponentFactory<PhysicsComponent>(max_size) {}

		// @@@@@ METHODS @@@@@ //
	public:
		PhysicsComponent * allocate(GameObject * gobj, const char * s, float mass, bool isBulletControlled);
	};
}



#endif