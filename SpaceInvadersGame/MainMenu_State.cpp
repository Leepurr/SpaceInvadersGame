#include "MainMenu_State.h"
#include "SceneManager.h"
#include "Character.h"

MainMenu_State::MainMenu_State(std::shared_ptr<SceneManager> sceneManager) :
GameState(sceneManager), p_sceneManager(sceneManager), p_renderer(new Renderer)
{
}

void MainMenu_State::Initialise(void)
{
	p_renderer->Initialse();
	auto player = std::make_shared<Character>();
	player->Load();
	player->SetPosition(Vector2D(p_renderer.get()->GetRenderBufferSize().Y - (player.get()->GetSize().x), 5));
	p_sceneManager->AddEntity(player);
}

void MainMenu_State::Cleanup(void)
{
}

void MainMenu_State::Resume(void)
{
}

void MainMenu_State::Pause(void)
{
}

void MainMenu_State::HandleEvents(void)
{
}

void MainMenu_State::Update(void)
{
	p_renderer->Update(p_sceneManager.get());
}

void MainMenu_State::Render(void)
{
	p_renderer->Render();
}
