#include "Game.h"

/*
Game::Game(void) :
_gameStateManager(new GameStateManager()), _SceneManager(new SceneManager),
_GameLevel(new GameLevel_State(_SceneManager.get())),
_MainMenu(new MainMenu_State(_SceneManager.get()))
*/
Game::Game(void) :
_gameStateManager(new GameStateManager()), _SceneManager(new SceneManager)
{
	_GameLevel = std::make_shared<GameLevel_State>(_SceneManager);
	_MainMenu = std::make_shared<MainMenu_State>(_SceneManager);
}
 
void Game::Start(void)
{
	_gameStateManager->Initialise();
}

void Game::Load(void)
{
 	_gameStateManager->PushState(std::move(_GameLevel));
	_gameStateManager->PushState(std::move(_MainMenu));
}

void Game::Update(void)
{
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
