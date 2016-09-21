#include "SceneManager.h"
#include "GObject.h"
#include <algorithm>
#include <string>

bool SceneManager::_isConstructed(false);

SceneManager::SceneManager(void)
{
	if (_isConstructed)
	{
		throw std::exception("A Scene Manager already exists!\n");
	}
	_isConstructed = true;
}

SceneManager::~SceneManager()
{
	_isConstructed = false;
}

bool SceneManager::AddEntity(std::shared_ptr<GObject> object)
{
	try
	{
		if (object != nullptr)
		{
			_gameObjects.push_back(std::move(object));
			return true;
		}
	}
	catch (std::exception e)
	{
		std::exception("An exception occured whilst trying to add an entity!\n");
	}
	return false;
}

bool SceneManager::DeleteEntity(std::shared_ptr<GObject> object)
{
	try
	{
		if (object != nullptr)
		{
			if (!_gameObjects.empty())
			{
				_gameObjects.erase(std::remove(_gameObjects.begin(), _gameObjects.end(), object), _gameObjects.end());
				return true;
			}
		}
	}
	catch (std::exception e)
	{
		std::exception("An exception occured whilst trying to delete an entity!\n");
	}
	return false;
}

GObject* SceneManager::GetGObjectByID(const std::string GObjectID) const
{
	if (!_gameObjects.empty())
	{
		std::vector<std::shared_ptr<GObject>>::const_iterator itr;
		for (itr = _gameObjects.begin(); itr != _gameObjects.end(); itr++)
		{
			std::string compareString = GObjectID;
			const std::string ID = (*itr).get()->GetObjectID();
			if (compareString.compare(ID))
			{
				return itr->get();
			}
		}
	}
	return nullptr;
}

const std::vector<std::shared_ptr<GObject>>& SceneManager::GetGObjects() const
{
	return _gameObjects;
}
