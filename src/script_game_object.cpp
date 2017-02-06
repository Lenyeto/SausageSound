#include <stdafx.h>
#include <script_game_object.h>
#include <log_manager.h>
#include <game_object.h>
#include <mesh_component.h>
#include <game_object_manager.h>
#include <mesh_component_factory.h>
#include <script_manager.h>
#include <physics_component_factory.h>



/// Was used for testing.



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



// The constructor for a gameobject.
int GameObject_new(lua_State * L)
{
	/// Checks the parameters of the stack.
	std::string group = luaL_checkstring(L, 1);

	std::string name = luaL_checkstring(L, 2);

	int tag = luaL_checkinteger(L, 3);

	
	std::string script = luaL_checkstring(L, 4);

	/// Runs the script.
	SCRIPT_MANAGER->runFile(script, true);
	
	/// Gets the gameobject group.
	lua_getglobal(L, "GameObjectGroups");
	lua_pushstring(L, group.c_str());
	lua_gettable(L, -2);

	/// Creates a new table for the gameobject.
	struct ScriptGameObject * temp = (ScriptGameObject *)lua_newuserdata(L, sizeof(struct ScriptGameObject));

	LOG_MANAGER->log(name);

	/// Creates the game object within the struct.
	temp->gObj = GAME_OBJECT_MANAGER->createGameObject(group, name, tag, nullptr);

	/// Splits up the fluff on the script string name.
	std::string tmp = script;
	int found = tmp.find_last_of(".");
	tmp.erase(tmp.begin() + found, tmp.end());
	found = tmp.find_last_of("\\");
	tmp = tmp.substr(found + 1, tmp.length());

	/// Sets the script name.
	temp->gObj->setScriptName(tmp);

	/// Sets the group of the game object.
	temp->gObj->setGroup(group);

	/// Gets the metatable for gameobject.
	luaL_getmetatable(L, "__GameObject__");

	lua_setmetatable(L, -2);

	lua_pushvalue(L, -1);

	lua_setfield(L, -3, name.c_str());

	/// Calls the onCreate method of the script.
	temp->gObj->callScriptMethod("onCreate");

	lua_pop(L, 1);

	/// Returns the top of the stack | The game object table.
	return 1;
}

/// Game objects index.
int GameObject_index(lua_State * L)
{
	/// Checks if the index input is a string.
	std::string indexed = luaL_checkstring(L, 2);

	/// Checks if the first part is a gameobject.
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	/// Gets the value from getField of the gameobject with the key of the indexed string.
	std::string value = go->gObj->getField(indexed);

	/// Checks if the indexed string is "name"
	if (indexed == "name")
	{
		/// Returns the name of the game object.
		lua_pushstring(L, go->gObj->getName().c_str());
	}
	else if (!value.empty())
	{
		/// Returns the value if one was returned from get field.
		lua_pushstring(L, value.c_str());
	}
	else {
		/// Returns the metatable of gameobject.
		luaL_getmetatable(L, "__GameObject__");

		lua_pushvalue(L, -2);

		lua_rawget(L, -2);
	}
	return 1;
}

/// The new index for gameobject for implacing values.
int GameObject_newIndex(lua_State * L)
{
	/// Gets the key string and checks if it is a string.
	std::string indexed = luaL_checkstring(L, 2);

	/// Checks if the value is a string.
	std::string value = luaL_checkstring(L, 3);

	/// Checks if the gameobject is indeed a gameobject.
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	/// Checks if its targetting name, which does nothing.
	if (indexed == "name")
	{

	}
	else
	{
		/// Sets a field in the gameobject.
		go->gObj->setField(indexed, value);
	}

	return 0;
}

/// Creates a mesh on the gameobject with the mesh that is the given string.
int GameObject_createMesh(lua_State * L)
{
	/// Checks if the argument was a string.
	std::string fname = luaL_checkstring(L, 2);

	/// Checks if the table is a gameobject.
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	/// Allocates a mesh for the game object.
	ssuge::MeshComponent * mesh = MESH_COMPONENT_FACTORY->allocate(go->gObj, fname);
	return 0;
}

/// SetScale wrapper for gameobject.
int GameObject_setScale(lua_State * L)
{
	if (lua_gettop(L) == 4)
	{
		ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");
		double x = luaL_checknumber(L, 2);
		double y = luaL_checknumber(L, 3);
		double z = luaL_checknumber(L, 4);

		go->gObj->setScale(x, y, z);
		return 0;
	}
	else {
		lua_pushstring(L, "Needs an x y and z for scale.");
		lua_error(L);
	}
	return 0;
}

/// SetPosition wrapper for gameobject.
int GameObject_setPosition(lua_State * L)
{
	if (lua_gettop(L) == 4)
	{
		ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");
		double x = luaL_checknumber(L, 2);
		double y = luaL_checknumber(L, 3);
		double z = luaL_checknumber(L, 4);

		go->gObj->setPosition(x, y, z);
		return 0;
	}
	else {
		lua_pushstring(L, "Needs an x y and z for position.");
		lua_error(L);
	}
	return 0;
}

/// SetPosition wrapper for gameobject.
int GameObject_getPosition(lua_State * L)
{
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	lua_pushnumber(L, go->gObj->getPosition().x);
	lua_pushnumber(L, go->gObj->getPosition().y);
	lua_pushnumber(L, go->gObj->getPosition().z);

	return 3;
}

/// SetVisible wrapper for gameobject.
int GameObject_setVisible(lua_State * L)
{
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	bool b;

	if (lua_isboolean(L, 2))
	{
		b = lua_toboolean(L, 2);
	}
	else
	{
		lua_pushstring(L, "ERROR : SET VISIBLE NEEDS A BOOLEAN.");
		lua_error(L);
	}

	go->gObj->setVisible(b);

	return 0;
}

/// GetTag wrapper for gameobject.
int GameObject_getTag(lua_State * L)
{

	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	lua_pushinteger(L, go->gObj->getTag());

	return 1;
}

/// GetName wrapper for gameobject.
int GameObject_getName(lua_State * L)
{
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	lua_pushstring(L, go->gObj->getName().c_str());

	return 1;
}

/// GetWorldPosition wrapper for gameobject.
int GameObject_getWorldPosition(lua_State * L)
{
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	lua_pushnumber(L, go->gObj->getWorldPosition().x);
	lua_pushnumber(L, go->gObj->getWorldPosition().y);
	lua_pushnumber(L, go->gObj->getWorldPosition().z);

	return 3;
}

/// GetOrientation wrapper for gameobject.
int GameObject_getOrientation(lua_State * L)
{
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	lua_pushnumber(L, go->gObj->getOrientation().w);
	lua_pushnumber(L, go->gObj->getOrientation().x);
	lua_pushnumber(L, go->gObj->getOrientation().y);
	lua_pushnumber(L, go->gObj->getOrientation().z);

	return 4;
}

/// SetOrientation wrapper for gameobject.
int GameObject_setOrientation(lua_State * L)
{
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	double w = luaL_checknumber(L, 2);
	double x = luaL_checknumber(L, 3);
	double y = luaL_checknumber(L, 4);
	double z = luaL_checknumber(L, 5);

	go->gObj->setOrientation(Ogre::Quaternion(w, x, y, z));

	return 0;
}

/// RotateLocal wrapper for gameobject.
int GameObject_rotateLocal(lua_State * L)
{
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");


	double degrees = luaL_checknumber(L, 2);
	double x = luaL_checknumber(L, 3);
	double y = luaL_checknumber(L, 4);
	double z = luaL_checknumber(L, 5);

	go->gObj->rotateLocal(degrees, x, y, z);

	return 0;
}

/// TransitionLocal wrapper for gameobject.
int GameObject_translateLocal(lua_State * L)
{
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	double z = luaL_checknumber(L, 4);

	go->gObj->translateLocal(x, y, z);

	return 0;
}

/// Lookat wrapper for gameobject.
int GameObject_lookat(lua_State * L)
{
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	double z = luaL_checknumber(L, 4);

	go->gObj->lookAt(x, y, z);

	return 0;
}

/// RotateWorld wrapper for gameobject.
int GameObject_rotateWorld(lua_State * L)
{
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	double degrees = luaL_checknumber(L, 2);
	double x = luaL_checknumber(L, 3);
	double y = luaL_checknumber(L, 4);
	double z = luaL_checknumber(L, 5);

	go->gObj->rotateWorld(degrees, x, y, z);

	return 0;
}

int GameObject_createPhysics(lua_State * L)
{
	ScriptGameObject * go = (ScriptGameObject*)luaL_checkudata(L, 1, "__GameObject__");

	const char * s = luaL_checkstring(L, 2);

	float mass = luaL_checknumber(L, 3);
	bool isBulletControlled;
	if (lua_isboolean(L, 4))
	{
		isBulletControlled = lua_toboolean(L, 4);

	}
	else {
		lua_pushstring(L, "Needed boolean for third argument");
	}


	PHYSICS_COMPONENT_FACTORY->allocate(go->gObj, s, mass, isBulletControlled);
	


	return 0;
}