#ifndef _SCRIPT_GAME_OBJECT_H_
#define _SCRIPT_GAME_OBJECT_H_

#include <stdafx.h>
#include <lua.hpp>
#include <game_object.h>




struct ScriptGameObject
{
public:
	ssuge::GameObject * gObj;
};

/// Prototypes for the gameobject table.
int GameObject_new(lua_State * L);

int GameObject_index(lua_State * L);

int GameObject_newIndex(lua_State * L);

int GameObject_createMesh(lua_State * L);

int GameObject_setScale(lua_State * L);

int GameObject_setPosition(lua_State * L);

int GameObject_getPosition(lua_State * L);

int GameObject_setVisible(lua_State * L);

int GameObject_getTag(lua_State * L);

int GameObject_getName(lua_State * L);

int GameObject_getWorldPosition(lua_State * L);

int GameObject_getOrientation(lua_State * L);

int GameObject_setOrientation(lua_State * L);

int GameObject_rotateLocal(lua_State * L);

int GameObject_translateLocal(lua_State * L);

int GameObject_lookat(lua_State * L);

int GameObject_rotateWorld(lua_State * L);

int GameObject_createPhysics(lua_State * L);

/// Method list for the GameObject table.
const struct luaL_Reg GameObject_methods[] =
{
	{ "new", GameObject_new },
	{ "__index", GameObject_index },
	{ "__newindex", GameObject_newIndex },
	{ "createMesh", GameObject_createMesh },
	{ "setScale", GameObject_setScale },
	{ "setPosition", GameObject_setPosition },
	{ "setVisible", GameObject_setVisible },
	{ "getTag", GameObject_getTag },
	{ "getName", GameObject_getName },
	{ "getWorldPosition", GameObject_getWorldPosition },
	{ "getOrientation", GameObject_getOrientation },
	{ "setOrientation", GameObject_setOrientation },
	{ "rotateLocal", GameObject_rotateLocal },
	{ "translateLocal", GameObject_translateLocal },
	{ "lookat", GameObject_lookat },
	{ "rotateWorld", GameObject_rotateWorld },
	{ "createPhysics", GameObject_createPhysics },
	{ NULL, NULL }
};



#endif