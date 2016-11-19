#pragma once
#include <memory>
#include "GameState.h"
#include "Renderer.h"
#include "Input.h"
#include "Event.h"

class SceneManager;
class GameStateManager;

class MainMenu_State : public GameState
{
private:
	int currentMenuItemAttribute; int generalMenuItemAttribute;
	std::unique_ptr<Renderer> p_renderer;
	std::shared_ptr<SceneManager> p_sceneManager;
	std::shared_ptr<GameStateManager> p_GameStateManager;
	bool quitRequested;
	enum class MenuItems
	{
		Play = 0,
		Options,  
		Leaderboard,
		Exit
	} _menuItems;
	Input _input;
	void EventHandle(const Event &events);
public:
	explicit MainMenu_State(std::shared_ptr<SceneManager> sceneManager,
				   std::shared_ptr<GameStateManager> gameStateManager);
	virtual ~MainMenu_State(void) = default;
	virtual void Initialise(void);
	virtual void Cleanup(void);
	virtual void Resume(void);
	virtual void Pause(void);
	virtual void HandleEvents(void);
	virtual void Update(void);
	virtual void Render(void);
	virtual const bool IsQuitRequested(void) const;

};