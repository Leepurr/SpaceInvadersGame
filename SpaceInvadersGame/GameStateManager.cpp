#include "GameStateManager.h"
#include "GameState.h"

void GameStateManager::Initialise(void)
{
}

void GameStateManager::Cleanup(void)
{
	for (std::shared_ptr<GameState>& itr : _states)
	{
		itr->Cleanup();
	}
	_states.clear();
}

void GameStateManager::ChangeState(std::shared_ptr<GameState> state)
{
	if (_states.empty())
	{
		_states.back()->Pause();
		_states.pop_back();
	}
	if (state != nullptr)
	{
		_states.push_back(state);
		_states.back()->Initialise();
	}
}

void GameStateManager::NextState()
{
	if (!_states.empty())
	{
		_states.back()->Pause();
	}
	//_states.front()->Initialise();
	_states.front()->Resume();
	
}

void GameStateManager::PushState(std::shared_ptr<GameState>&& state)
{
	if (!_states.empty())
	{
		_states.back()->Pause();
	}
	if (state != nullptr)
	{
		_states.push_back(std::move(state));
		_states.back()->Initialise();
	}
}

void GameStateManager::PopState(void)
{
	if (!_states.empty())
	{
		_states.back()->Cleanup();
		_states.pop_back();
	}
}

void GameStateManager::HandleEvents(void)
{
	_states.back()->HandleEvents();
}

void GameStateManager::Update(void)
{
	_states.back()->Update();
}
 
void GameStateManager::Render(void)
{
	_states.back()->Render();
}

const bool GameStateManager::IsQuitRequestedByCurrentGameState() const
{
	return _states.back()->IsQuitRequested();
}
