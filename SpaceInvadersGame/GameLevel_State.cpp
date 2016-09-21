#include "GameLevel_State.h"
#include "SceneManager.h"

GameLevel_State::GameLevel_State(std::shared_ptr<SceneManager> sceneManager) :
GameState(sceneManager), p_sceneManager(sceneManager), p_renderer(new Renderer)
{

}

void GameLevel_State::Initialise(void)
{
	p_renderer->Initialse();
}

void GameLevel_State::Cleanup(void)
{
}

void GameLevel_State::Resume(void)
{
}

void GameLevel_State::Pause(void)
{
}

void GameLevel_State::HandleEvents(void)
{
}

void GameLevel_State::Update(void)
{
	p_renderer->Update(p_sceneManager.get());
}

void GameLevel_State::Render(void)
{
	p_renderer->Render();
}
