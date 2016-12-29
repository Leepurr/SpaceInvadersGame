#pragma once
#include <vector>
#include <memory>

class GObject;

class SceneManager
{
private:
	static bool _isConstructed;											//Used to determine if a SceneManger already exists
	std::vector<std::shared_ptr<GObject>> _gameObjects;
public:
	explicit SceneManager(void);
	~SceneManager();
	const bool AddEntity(std::shared_ptr<GObject> object);
	const bool DeleteEntity(std::shared_ptr<GObject> object);
	const bool SceneManager::DeleteEntityByName(std::string objectName);
	const GObject* GetGObjectByID(const std::string GObjectID) const;
	const std::shared_ptr<GObject>&  GetObjectByName(const std::string GObjectName) const;
	const std::vector<std::shared_ptr<GObject>>& GetGObjects() const;
};