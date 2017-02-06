#ifndef _SCRIPT_FUNCTIONS_H_
#define _SCRIPT_FUNCTIONS_H_
#include <lua.hpp>


/// Global Method prototypes.

int log(lua_State * L);

int registerListener(lua_State * L);

int isActionActive(lua_State * L);

int createGameGroup(lua_State * L);

int getDT(lua_State * L);

int getAxis(lua_State * L);

int quit(lua_State * L);

int setGravity(lua_State * L);


/// List of Global Methods
static luaL_Reg global_methods[]
{
	{ "log", log },
	{ "registerListener", registerListener },
	{ "isActionActive", isActionActive },
	{ "createGameGroup", createGameGroup },
	{ "getDT", getDT },
	{ "getAxis", getAxis },
	{ "quit", quit },
	{ "setGravity", setGravity },
	{ NULL, NULL }
};


#endif