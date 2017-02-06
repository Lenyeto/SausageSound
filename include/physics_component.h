#ifndef _PHYSICS_COMPONENT_H_
#define _PHYSICS_COMPONENT_H_

#include <stdafx.h>
#include <component.h>
#include <physics_component_factory.h>
#include <btBulletDynamicsCommon.h>

namespace ssuge
{
	/// The Mesh component is an instance of a mesh -- we'll later add kinematic animation
	/// support here.
	class PhysicsComponent : public Component
	{
		// @@@@@ ATTRIBUTES @@@@@ //
	protected:
		GameObject * mGameObject;
		btRigidBody * mRigidBody;
		bool isAffectedByBullet;

		// @@@@@ CONSTRUCTORS / DESTRUCTORS @@@@@ //
	protected:
		/// Creates a PhysicsComponent
		PhysicsComponent(GameObject * p, const char * s, float mass, bool isBulletControlled);

		/// The destructor
		virtual ~PhysicsComponent();

		// @@@@@ GETTERS / SETTERS @@@@@ //
	public:
		/// Gets the type of this component (ComponentType::MESH)
		ComponentType getType() { return ComponentType::MESH; }

		// @@@@@ METHODS @@@@@ //
	public:
		/// Updates the component.  Overrident from Component  
		virtual void update(float dt) override;

		// @@@@@ FRIENDS @@@@@ //
		/// The MeshComponentFactory is a friend so they can access our private
		/// constructor.
		friend class PhysicsComponentFactory;
	};
}


#endif