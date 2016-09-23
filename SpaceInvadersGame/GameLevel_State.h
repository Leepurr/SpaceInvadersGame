#pragma once
#include <memory>
#include "GameState.h"
#include "Renderer.h"
#include "Input.h"

class SceneManager;

class GameLevel_State : public GameState
{
private:
	bool quitRequested;
	std::unique_ptr<Renderer> p_renderer;
	std::shared_ptr<SceneManager> p_sceneManager;
	Input _input;
public:
	GameLevel_State(std::shared_ptr<SceneManager>);
	virtual ~GameLevel_State(void) = default;
	virtual void Initialise(void);
	virtual void Cleanup(void);
	virtual void Resume(void);
	virtual void Pause(void);
	virtual void HandleEvents(void);
	virtual void Update(void);
	virtual void Render(void);
	virtual const bool IsQuitRequested(void) const;
};