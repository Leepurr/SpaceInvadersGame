#include "MainMenu_State.h"
#include "SceneManager.h"
#include "Character.h"


static bool sg_drawScreen = true;

MainMenu_State::MainMenu_State(std::shared_ptr<SceneManager> sceneManager) :
GameState(sceneManager), p_sceneManager(sceneManager), p_renderer(new Renderer),
currentMenuItemAttribute(0), generalMenuItemAttribute(0) , _menuItems(MenuItems::Play),
quitRequested(false)
{}

void MainMenu_State::Initialise(void)
{
	p_renderer->Initialse(0);
	currentMenuItemAttribute = FOREGROUND_RED + FOREGROUND_INTENSITY;
	generalMenuItemAttribute = FOREGROUND_BLUE + FOREGROUND_INTENSITY;
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
	if(_input.isKeyDown(VK_DOWN))
	{
		switch (_menuItems)
		{
		case MenuItems::Play:
			_menuItems = MenuItems::Options;
			break;
		case MenuItems::Options:
			_menuItems = MenuItems::Leaderboard;
			break;
		case MenuItems::Leaderboard:
			_menuItems = MenuItems::Exit;
			break;
		case MenuItems::Exit:
			_menuItems = MenuItems::Play;
			break;
		}
		sg_drawScreen = true;
	}
	else if (_input.isKeyDown(VK_UP))
	{
		switch (_menuItems)
		{
		case MenuItems::Play:
			_menuItems = MenuItems::Exit;
			break;
		case MenuItems::Options:
			_menuItems = MenuItems::Play;
			break;
		case MenuItems::Leaderboard:
			_menuItems = MenuItems::Options;
			break;
		case MenuItems::Exit:
			_menuItems = MenuItems::Leaderboard;
			break;
		}
		sg_drawScreen = true;
	}
	if (_input.isKeyDown(VK_RETURN))
	{
		switch (_menuItems)
		{
		case MenuItems::Play:

			break;
		case MenuItems::Options:
			
			break;
		case MenuItems::Leaderboard:
			
			break;
		case MenuItems::Exit:
			quitRequested = true;
			break;
		}
	}
}

void MainMenu_State::Update(void)
{
	//p_renderer->Update(p_sceneManager.get());
	if (sg_drawScreen)
	{
		Vector2D Position = { p_renderer->GetRenderBufferSize().X / 2, (p_renderer->GetRenderBufferSize().Y / 2) - 5 };
		if (_menuItems == MenuItems::Play)
		{
			p_renderer->RenderText("Play", currentMenuItemAttribute, Position);
		}
		else
		{
			p_renderer->RenderText("Play", generalMenuItemAttribute, Position);
		}
		Position.y += 2;
		if (_menuItems == MenuItems::Options)
		{
			p_renderer->RenderText("Options", currentMenuItemAttribute, Position);
		}
		else
		{
			p_renderer->RenderText("Options", generalMenuItemAttribute, Position);
		}
		Position.y += 2;
		if (_menuItems == MenuItems::Leaderboard)
		{
			p_renderer->RenderText("Leaderboard", currentMenuItemAttribute, Position);
		}
		else
		{
			p_renderer->RenderText("Leaderboard", generalMenuItemAttribute, Position);
		}
		Position.y += 2;
		if (_menuItems == MenuItems::Exit)
		{
			p_renderer->RenderText("Exit", currentMenuItemAttribute, Position);
		}
		else
		{
			p_renderer->RenderText("Exit", generalMenuItemAttribute, Position);
		}
	}
	Sleep(40);
}

void MainMenu_State::Render(void)
{
	if (sg_drawScreen)
	{
		p_renderer->Render();
		sg_drawScreen = false;
	}
}

const bool MainMenu_State::IsQuitRequested(void) const
{
	return quitRequested;
}
