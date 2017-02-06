#ifndef _SCRIPT_MANAGER_H_
#define _SCRIPT_MANAGER_H_

#include <stdafx.h>
#include <singleton.h>
#include <input_manager.h>
#include <game_object_manager.h>
#include <lua.hpp>
#include <script_functions.h>

#define SCRIPT_MANAGER ssuge::ScriptManager::getSingletonPtr()

namespace ssuge
{
	class ScriptManager : public Singleton<ScriptManager>
	{
		// @@@@@ MEMBER VARIABLES @@@@@ //
	protected:
		/// The lua state that the game uses.
		lua_State * mLuaState;
		/// DTime as I dont know where else to place it for now.
		float dtime;
		// @@@@@ Constructors and Destructors @@@@@ //
	public:
		/// Default Constructor
		ScriptManager();

		/// Destructor
		virtual ~ScriptManager();
		// @@@@@ METHODS @@@@@ //
	public:
		/// Runs a lua file.
		void runFile(std::string fileName, bool hasReturn = false);

		/// Executes a script, for internal use.
		void executeScript(std::string group, std::string name, std::string script, std::string methodName);

		/// Wasnt sure where to get and place the dtime that is calculated in the application loop.
		void setDT(float dt);
		float getDT() const { return dtime; };
	};
}



#endif


