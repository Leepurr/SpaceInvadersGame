#pragma once
#include <memory>
#include "Renderer.h"

class SceneManager;

class GameState
{
public:
	explicit GameState() = default;
	virtual ~GameState(void) = default;
	virtual void Initialise(void) = 0;
	virtual void Cleanup(void) = 0;
	virtual void Resume(void) = 0;
	virtual void Pause(void) = 0;
	virtual void HandleEvents(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
	virtual const bool IsQuitRequested(void) const = 0;
};