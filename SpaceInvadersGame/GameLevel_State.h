#pragma once
#include <memory>
#include "GameState.h"
#include "Renderer.h"

class SceneManager;

class GameLevel_State : public GameState
{
private:
	std::unique_ptr<Renderer> p_renderer;
	std::shared_ptr<SceneManager> p_sceneManager;
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
};