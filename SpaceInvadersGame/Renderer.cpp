#include "Renderer.h"
#include "SceneManager.h"
#include "Character.h"

void Renderer::Initialse(void)
{
	_stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(_stdOutputHandle, &_consoleScreenBufferInfo);
	_renderDataBuffer.resize(_consoleScreenBufferInfo.dwSize.X * _consoleScreenBufferInfo.dwSize.Y);
	for (CHAR_INFO& itr : _renderDataBuffer)
	{
		itr.Attributes = BACKGROUND_RED;
		itr.Char.AsciiChar = ' ';
		itr.Char.UnicodeChar = ' ';
	}
	COORD firstCell = { 0,0 };
	_renderRegion.Left = 0;											//The x-coordinate of the upper left corner of the rectangle.
	_renderRegion.Top = 0;											//The y-coordinate of the upper left corner of the rectangle.
	_renderRegion.Right = (_consoleScreenBufferInfo.dwSize.X - 1);  //The x-coordinate of the lower right corner of the rectangle.
	_renderRegion.Bottom = (_consoleScreenBufferInfo.dwSize.Y - 1); //The y-coordinate of the lower right corner of the rectangle.
	WriteConsoleOutput(_stdOutputHandle, _renderDataBuffer.data(), _consoleScreenBufferInfo.dwSize, firstCell, &_renderRegion);
	render_X = 0; render_Y = 0;
}

void Renderer::Render(void) 
{
	COORD firstCell = { 0,0 };
	WriteConsoleOutput(_stdOutputHandle, _renderDataBuffer.data(), _consoleScreenBufferInfo.dwSize, firstCell, &_renderRegion);
}


void Renderer::Update(SceneManager* sceneManager)
{
	int globalCounter = 0;
	ClearRenderBuffer();
	try
	{
		if (!sceneManager->GetGObjects().empty())
		{
			for (auto &objItr : sceneManager->GetGObjects())
			{
				int positionX = (((objItr.get()->GetPosition().x - 1) * _consoleScreenBufferInfo.dwSize.X));
				int finalXPosition = positionX;
				globalCounter = 0;
				switch (objItr.get()->GetObjectType())
				{
				case Etype::Player:
					for (render_X = 0; render_X < objItr.get()->GetSize().x; render_X++)
					{
						finalXPosition = positionX + (render_X * _consoleScreenBufferInfo.dwSize.X);
						for (render_Y = 0; render_Y < objItr.get()->GetSize().y; render_Y++)
						{
							_renderDataBuffer.at((finalXPosition + objItr.get()->GetPosition().y) + render_Y)
								.Char.AsciiChar = objItr.get()->GetRenderData().at(globalCounter).Char.AsciiChar;
							_renderDataBuffer.at((finalXPosition + objItr.get()->GetPosition().y) + render_Y)
								.Char.UnicodeChar = objItr.get()->GetRenderData().at(globalCounter).Char.UnicodeChar;
							_renderDataBuffer.at((finalXPosition + objItr.get()->GetPosition().y) + render_Y)
								.Attributes = objItr.get()->GetRenderData().at(globalCounter).Attributes;
							globalCounter++;
						}
					}
					break;
				case Etype::Standard:
					for (render_X = 0; render_X < objItr.get()->GetSize().x; render_X++)
					{
						finalXPosition = positionX + (render_X * _consoleScreenBufferInfo.dwSize.X);
						for (render_Y = 0; render_Y < objItr.get()->GetSize().y; render_Y++)
						{
							_renderDataBuffer.at((finalXPosition + objItr.get()->GetPosition().y) + render_Y)
								.Char.AsciiChar = objItr.get()->GetRenderData().at(globalCounter).Char.AsciiChar;
							_renderDataBuffer.at((finalXPosition + objItr.get()->GetPosition().y) + render_Y)
								.Char.UnicodeChar = objItr.get()->GetRenderData().at(globalCounter).Char.UnicodeChar;
							_renderDataBuffer.at((finalXPosition + objItr.get()->GetPosition().y) + render_Y)
								.Attributes = objItr.get()->GetRenderData().at(globalCounter).Attributes;
							globalCounter++;
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}
	catch(std::exception e)
	{
		std::runtime_error(e.what());
	}
}

void Renderer::ClearRenderBuffer()
{
	for (auto &itr : _renderDataBuffer)
	{
		itr.Char.AsciiChar = ' ';
		itr.Char.UnicodeChar = ' ';
		itr.Attributes = 0;
	}
}