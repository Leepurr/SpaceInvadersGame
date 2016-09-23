#pragma once
#include <memory>
#include <vector>
#include "GameState.h"

class GameStateManager
{
private:
	std::vector<std::shared_ptr<GameState>> _states;
public:
	GameStateManager(void) {};
	~GameStateManager(void) {};
	void Initialise(void);
	void Cleanup(void);

	void ChangeState(std::shared_ptr<GameState> state);
	void PushState(std::shared_ptr<GameState>&& state);
	void PopState(void);

	void HandleEvents(void);
	void Update(void);
	void Render(void);
	
	const bool IsQuitRequestedByCurrentGameState() const;
};

