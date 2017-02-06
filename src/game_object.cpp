#include <stdafx.h>
#include <game_object.h>
#include <application.h>
#include <script_manager.h>


ssuge::GameObject::GameObject(unsigned int tag, std::string name, GameObject * parent) : mTag(tag), mName(name)
{
	if (parent)
		mSceneNode = parent->getSceneNode()->createChildSceneNode(name);
	else
		mSceneNode = APPLICATION->getSceneManager()->getRootSceneNode()->createChildSceneNode(name);
	
	// Register this scene node as a Node::Listener
	mSceneNode->setListener(this);

	// A little trick (I wasn't expecting you to uncover this on your own).  Here I'm attaching
	// our GameObject* for this node as a "user-field" in a dictionary stored internally in the
	// scene node object.
	Ogre::UserObjectBindings & bindings = mSceneNode->getUserObjectBindings();
	bindings.setUserAny("game_object", Ogre::Any(this));
}


ssuge::GameObject::~GameObject()
{
	// Remove ourself as a listener to this node
	mSceneNode->setListener(NULL);

	// Destroy our components
	std::map<ComponentType, Component*>::iterator iter = mComponents.begin();
	while (iter != mComponents.end())
	{
		delete iter->second;
		iter->second = nullptr;
		++iter;
	}
	mComponents.clear();

	// Detach our scene node from its parent.  We might not have one if an ancestor
	// node was destroyed before us.  Not an error...(I think)
	if (mSceneNode->getParentSceneNode())
	{
		mSceneNode->getParentSceneNode()->removeChild(mSceneNode);
	}
	APPLICATION->getSceneManager()->destroySceneNode(mSceneNode);
	mSceneNode = NULL;
}


void ssuge::GameObject::setScriptName(std::string sName)
{
	mScriptName = sName;
}

void ssuge::GameObject::callScriptMethod(std::string methodName)
{
	SCRIPT_MANAGER->executeScript(mGroup, mName, mScriptName, methodName);
}

void ssuge::GameObject::setGroup(std::string groupName)
{
	mGroup = groupName;
}

void ssuge::GameObject::removeComponent(ssuge::ComponentType t)
{
	std::map<ComponentType, Component*>::iterator iter = mComponents.find(t);
	if (iter != mComponents.end())
		mComponents.erase(iter);
}


void ssuge::GameObject::addComponent(ssuge::Component * c)
{
	// Delete the existing component of that type, if there is one
	std::map<ComponentType, Component*>::iterator iter = mComponents.find(c->getType());
	if (iter != mComponents.end())
		delete iter->second;
	mComponents[c->getType()] = c;
}


/// Sets a value to a key in mFields.
void ssuge::GameObject::setField(std::string key, std::string value)
{
	mFields[key] = value;
}


/// Returns a value from a key in mFields.
std::string ssuge::GameObject::getField(std::string key)
{
	return mFields[key];
}


ssuge::Component* ssuge::GameObject::getComponent(ssuge::ComponentType t)
{
	// Make sure we have one of those types -- otherwise, we'll actually create a garbage pointer.
	std::map<ComponentType, Component*>::iterator it = mComponents.find(t);
	if (it != mComponents.end())
	{
		return it->second;
	}
	else
		return nullptr;
}


void ssuge::GameObject::nodeUpdated(const Ogre::Node * n) 
{
	std::map<ComponentType, Component*>::iterator iter = mComponents.begin();
	while (iter != mComponents.end())
	{
		iter->second->nodeUpdated(n);
		++iter;
	}
}



void ssuge::GameObject::update(float dt) 
{
	/// Checks if there is a script on this game object, if there is it runs onUpdate method.
	if (!mScriptName.empty())
	{
		callScriptMethod("onUpdate");
	}
		

	std::map<ComponentType, Component*>::iterator it = mComponents.begin();
	while (it != mComponents.end())
	{
		it->second->update(dt);
		++it;
	}
}

void ssuge::GameObject::handleAction(std::string action, bool isStarting)
{
	/// Checks if there is a script on this game object, if there is it runs onAction method.
	if (!mScriptName.empty())
	{
		callScriptMethod("onAction");
	}
}


void ssuge::GameObject::setVisible(bool isVisible)
{
	mSceneNode->setVisible(isVisible, true);
}