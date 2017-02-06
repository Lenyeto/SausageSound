#include <stdafx.h>
#include <physics_component_factory.h>
#include <physics_component.h>
#include <game_object.h>

// A template-specialization of the msSingleton attribute for the PhysicsComponentFactory class
template<> ssuge::PhysicsComponentFactory * ssuge::Singleton<ssuge::PhysicsComponentFactory>::msSingleton = nullptr;

ssuge::PhysicsComponent * ssuge::PhysicsComponentFactory::allocate(ssuge::GameObject * gobj, const char * s, float mass, bool isBulletControlled)
{
	PhysicsComponent * pc = new PhysicsComponent(gobj, s, mass, isBulletControlled);

	

	gobj->addComponent(pc);
	storePtr(pc);
	return pc;
}