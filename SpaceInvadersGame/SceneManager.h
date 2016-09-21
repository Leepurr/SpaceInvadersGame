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
	bool AddEntity(std::shared_ptr<GObject> object);
	bool DeleteEntity(std::shared_ptr<GObject> object);
	GObject* GetGObjectByID(const std::string GObjectID) const;
	const std::vector<std::shared_ptr<GObject>>& GetGObjects() const;
};