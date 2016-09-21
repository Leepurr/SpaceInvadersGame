#pragma once
#include <memory>
#include "GameStateManager.h"
#include "GameLevel_State.h"
#include "MainMenu_State.h"
#include "SceneManager.h"

class Game
{
private:  
	std::unique_ptr<GameStateManager>	_gameStateManager;
	std::shared_ptr<SceneManager>		_SceneManager;
	std::shared_ptr<GameLevel_State>	_GameLevel;
	std::shared_ptr<MainMenu_State>		_MainMenu;
public:
	Game(void);
	~Game(void) {};
	void Start(void);
	void Load(void);
	void Update(void);
	void Render(void);
	GameStateManager* GetGameStateManager() { return _gameStateManager.get(); }
};

