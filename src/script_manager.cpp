#include <stdafx.h>
#include <script_manager.h>
#include <log_manager.h>
#include <script_game_object.h>
#include <game_object_manager.h>
#include <input_manager.h>

/// Sets the singleton to a nullptr.
template<> ssuge::ScriptManager * ssuge::Singleton<ssuge::ScriptManager>::msSingleton = nullptr;


/// Was used for testing.
/*
static void stackDump(lua_State * L)
{
	printf("/// STACK DUMP\n");
	for (int i = 1; i <= lua_gettop(L); i++)
	{
		if (lua_isnumber(L, i))
		{
			double num = lua_tonumber(L, i);
			printf("%d: number(%f)\n", i, num);
		}
		else if (lua_isstring(L, i))
		{
			const char * str = lua_tostring(L, i);
			printf("%d: string('%s')\n", i, str);
		}
		else if (lua_istable(L, i))
		{
			printf("%d: table\n", i);
		}
		else if (lua_isfunction(L, i))
		{
			printf("%d: function\n", i);
		}
		else if (lua_isuserdata(L, i))
		{
			printf("%d: userdata\n", i);
		}
		else if (lua_isnil(L, i))
		{
			printf("%d: nil\n", i);
		}
		else
		{
			printf("%d: ???\n", i);
		}


	}
	printf("\\\\\\ end STACK DUMP\n");
}
*/

/// Runs a lua file, if a return is expected then it adds it to the global table.
void ssuge::ScriptManager::runFile(std::string fileName, bool hasReturn)
{
	/// Creates a lua state for error handling.
	lua_State *state = luaL_newstate();

	/// Stores the result from load file for error handling.
	int result = luaL_loadfile(mLuaState, fileName.c_str());
	
	/// Handles errors.
	if (result != LUA_OK)
	{
		const char* message = lua_tostring(state, -1);
		
		/// Logs the error.
		LOG_MANAGER->log(message);

		lua_pop(state, 1);
		return;
	}

	/// Attempts to run the loaded lua file.
	result = lua_pcall(mLuaState, 0, LUA_MULTRET, 0);

	/// Handles the error of the lua file if it fails to run.
	if (result != LUA_OK)
	{
		const char* message = lua_tostring(state, -1);

		///Logs the error.
		LOG_MANAGER->log(message);

		lua_pop(state, 1);
		return;
	}

	/// If the file is expecting a return it adds it to the global table.
	if (hasReturn)
	{
		/// Checks if the top of the stack is not a table.
		if (!lua_istable(mLuaState, -1))
		{
			const char * errstring = "ERROR: THIS CURRENTLY ONLY WORKS WITH TABLES";
			
			lua_pushstring(mLuaState, errstring);
			lua_error(mLuaState);
		}

		/// Takes off the .lua and the \\s.
		int found = fileName.find_last_of(".");
		fileName.erase(fileName.begin() + found, fileName.end());
		found = fileName.find_last_of("\\");
		fileName = fileName.substr(found + 1, fileName.length());

		lua_setglobal(mLuaState, fileName.c_str());
	}
}

/// IGNORE THIS | IDK WHERE TO PUT IT
void ssuge::ScriptManager::setDT(float dt)
{
	// Sets the dtime.
	dtime = dt;
}

///Executes a script for a game object with a given method from a specified script.
void ssuge::ScriptManager::executeScript(std::string group, std::string name, std::string script, std::string methodName)
{
	/// Gets the script and gets the function from that.
	lua_getglobal(mLuaState, script.c_str());
	lua_getfield(mLuaState, -1, methodName.c_str());

	/// Gets the gameobject from the groups.
	lua_getglobal(mLuaState, "GameObjectGroups");
	lua_getfield(mLuaState, -1, group.c_str());
	lua_getfield(mLuaState, -1, name.c_str());

	///Removes clutter from the stack.
	lua_remove(mLuaState, -2);
	lua_remove(mLuaState, -2);

	///Runs the method on the game object.
	lua_pcall(mLuaState, 1, 0, 0);
}

extern "C" {
	///Scriptmanager constructor.
	ssuge::ScriptManager::ScriptManager()
	{
		/// Creates the new lua state.
		mLuaState = luaL_newstate();

		/// Adds the libraries to the lua state.
		luaL_openlibs(mLuaState);
		lua_newtable(mLuaState);

		/// Gets the global table and adds the global methods to it.
		lua_getglobal(mLuaState, "_G");
		luaL_setfuncs(mLuaState, global_methods, 0);

		/// Creates the Game Object meta table, adds the methods, and adds it to the global table.
		luaL_newmetatable(mLuaState, "__GameObject__");
		luaL_setfuncs(mLuaState, GameObject_methods, 0);
		lua_setglobal(mLuaState, "GameObject");

		/// Adds a GameObjectGroups table to the global table.
		lua_newtable(mLuaState);
		lua_setglobal(mLuaState, "GameObjectGroups");

	}
}

/// Closes the lua state when the scriptmanager gets destructed.
ssuge::ScriptManager::~ScriptManager()
{
	lua_close(mLuaState);
}