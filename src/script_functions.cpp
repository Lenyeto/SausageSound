#include <stdafx.h>
#include <script_functions.h>
#include <lua.hpp>
#include <log_manager.h>
#include <script_game_object.h>
#include <input_manager.h>
#include <game_object_manager.h>
#include <script_manager.h>
#include <application.h>

/// Log wrapper for lua.
int log(lua_State * L)
{
	if (lua_isstring(L, 1))
	{
		LOG_MANAGER->log(lua_tostring(L, 1));
	}
	return 0;
}

/// RegisterListener Wrapper for lua.
int registerListener(lua_State * L)
{
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");
	INPUT_MANAGER->addListener(go->gObj);
	return 0;
}

/// isActionActive wrapper.
int isActionActive(lua_State * L)
{
	std::string string = luaL_checkstring(L, 1);
	bool b = INPUT_MANAGER->isActionActive(string);
	lua_pushboolean(L, b);
	return 1;
}

/// CreateGameGroup wrapper.
int createGameGroup(lua_State * L)
{
	std::string groupname = luaL_checkstring(L, 1);

	GAME_OBJECT_MANAGER->createGroupName(groupname);

	lua_getglobal(L, "GameObjectGroups");
	lua_newtable(L);
	lua_setfield(L, -2, groupname.c_str());

	return 0;
}

/// returns the delta time of the games frames.
int getDT(lua_State * L)
{
	lua_pushnumber(L, SCRIPT_MANAGER->getDT());
	return 1;
}

/// getAxis wrapper.
int getAxis(lua_State * L)
{
	std::string string = luaL_checkstring(L, 1);
	double a = INPUT_MANAGER->getAxisValue(string);
	lua_pushnumber(L, a);
	return 1;
}

/// quit wrapper.
int quit(lua_State * L)
{
	APPLICATION->quit();
	return 0;
}


int setGravity(lua_State * L)
{
	float x = luaL_checknumber(L, 1);
	float y = luaL_checknumber(L, 2);
	float z = luaL_checknumber(L, 3);

	btVector3 * vect = &btVector3(x, y, z);

	PHYSICS_MANAGER->setGravity(vect);

	return 0;
}