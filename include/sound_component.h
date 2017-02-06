#ifndef _SOUND_COMPONENT_H_
#define _SOUND_COMPONENT_H_

#include <stdafx.h>
#include <component.h>
#include <irrKlang.h>

namespace ssuge
{
	/// The Mesh component is an instance of a mesh -- we'll later add kinematic animation
	/// support here.
	class SoundComponent : public Component
	{
		// @@@@@ ATTRIBUTES @@@@@ //
	protected:
		irrklang::ISound * mSound;

		// @@@@@ CONSTRUCTORS / DESTRUCTORS @@@@@ //
	protected:
		/// Creates a MeshComponent -- Note: I made this protected to force the user
		/// to go through the MeshComponentFactory (below)
		SoundComponent(GameObject * p, std::string fname);

		/// The destructor
		virtual ~SoundComponent();

		// @@@@@ GETTERS / SETTERS @@@@@ //
	public:
		/// Gets the type of this component (ComponentType::MESH)
		//ComponentType getType() { return ComponentType::MESH; }

		// @@@@@ METHODS @@@@@ //
	public:
		/// Updates the component.  Overrident from Component  
		virtual void update(float dt) override;

		void play();

		/*
		// @@@@@ FRIENDS @@@@@ //
		/// The MeshComponentFactory is a friend so they can access our private
		/// constructor.
		friend class MeshComponentFactory;
		*/
	};
}

#endif
