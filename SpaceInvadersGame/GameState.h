#pragma once
#include <memory>
#include "Renderer.h"

class SceneManager;


class GameState
{
private:
	Renderer _renderer;
public:
	explicit GameState(std::shared_ptr<SceneManager>) {};
	virtual ~GameState(void) = default;
	virtual void Initialise(void) = 0;
	virtual void Cleanup(void) = 0;
	virtual void Resume(void) = 0;
	virtual void Pause(void) = 0;
	virtual void HandleEvents(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
};