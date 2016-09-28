#include "GameLevel_State.h"
#include "SceneManager.h"
#include "Character.h"

GameLevel_State::GameLevel_State(std::shared_ptr<SceneManager> sceneManager) :
GameState(sceneManager), p_sceneManager(sceneManager), p_renderer(new Renderer),
quitRequested(false)
{}

void GameLevel_State::Initialise(void)
{
	p_renderer->Initialse(0);
	auto player = std::make_shared<Character>();
	player->Load();
	player->SetPosition(Vector2D<int>(p_renderer.get()->GetRenderBufferSize().Y - (player.get()->GetSize().GetX()), 5));
	p_sceneManager->AddEntity(player);
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
	if (_input.isKeyDown(VK_LEFT))
	{
		p_sceneManager->GetObjectByName("Character");

	}
	p_renderer->Update(p_sceneManager.get());
}

void GameLevel_State::Render(void)
{
	p_renderer->Render();
}

const bool GameLevel_State::IsQuitRequested(void) const
{
	return quitRequested;
}
