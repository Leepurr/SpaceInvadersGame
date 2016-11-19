#include "Game.h"

Game::Game(void) :
_EventManager(new EventManager), _gameStateManager(new GameStateManager()), 
_SceneManager(new SceneManager)
{
	_GameLevel = std::make_shared<GameLevel_State>(_SceneManager);
	_MainMenu = std::make_shared<MainMenu_State>(_SceneManager, _gameStateManager);
}
 
void Game::Start(void)
{
	_gameStateManager->Initialise();
}

void Game::Load(void)
{
//	_gameStateManager->PushState(std::move(_MainMenu));
	_gameStateManager->PushState(std::move(_GameLevel));
	
}

void Game::Update(void)
{
	_EventManager->Update();
	_gameStateManager->HandleEvents();
	_gameStateManager->Update();
}

void Game::Render(void)
{
	_gameStateManager->Render();
}

const bool Game::isQuitRequested() const
{
	return _gameStateManager->IsQuitRequestedByCurrentGameState();
}
