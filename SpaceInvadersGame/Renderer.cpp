#include "Renderer.h"
#include "SceneManager.h"
#include "Character.h"

void Renderer::Initialse(const int backgroundAttributes)
{
	_stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(_stdOutputHandle, &_consoleScreenBufferInfo);
	_renderDataBuffer.resize(_consoleScreenBufferInfo.dwSize.X * _consoleScreenBufferInfo.dwSize.Y);
	for (CHAR_INFO& itr : _renderDataBuffer)
	{
		itr.Attributes = backgroundAttributes;
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

void Renderer::ClearRenderBuffer()
{
	for (auto &itr : _renderDataBuffer)
	{
		itr.Char.AsciiChar = ' ';
		itr.Char.UnicodeChar = ' ';
		itr.Attributes = 0;
	}
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
				int positionX = (((objItr.get()->GetPosition().GetX() - 1) * _consoleScreenBufferInfo.dwSize.X));
				int finalXPosition = positionX;
				globalCounter = 0;
				switch (objItr.get()->GetObjectType())
				{
				case Etype::Player:
					for (render_X = 0; render_X < objItr.get()->GetSize().GetX(); render_X++)
					{
						finalXPosition = positionX + (render_X * _consoleScreenBufferInfo.dwSize.X);
						for (render_Y = 0; render_Y < objItr.get()->GetSize().GetY(); render_Y++)
						{
							_renderDataBuffer.at((finalXPosition + objItr.get()->GetPosition().GetY()) + render_Y)
								.Char.AsciiChar = objItr.get()->GetRenderData().at(globalCounter).Char.AsciiChar;
							_renderDataBuffer.at((finalXPosition + objItr.get()->GetPosition().GetY()) + render_Y)
								.Char.UnicodeChar = objItr.get()->GetRenderData().at(globalCounter).Char.UnicodeChar;
							_renderDataBuffer.at((finalXPosition + objItr.get()->GetPosition().GetY()) + render_Y)
								.Attributes = objItr.get()->GetRenderData().at(globalCounter).Attributes;
							globalCounter++;
						}
					}
					break;
				case Etype::Standard:
					for (render_X = 0; render_X < objItr.get()->GetSize().GetX(); render_X++)
					{
						finalXPosition = positionX + (render_X * _consoleScreenBufferInfo.dwSize.X);
						for (render_Y = 0; render_Y < objItr.get()->GetSize().GetY(); render_Y++)
						{
							_renderDataBuffer.at((finalXPosition + objItr.get()->GetPosition().GetY()) + render_Y)
								.Char.AsciiChar = objItr.get()->GetRenderData().at(globalCounter).Char.AsciiChar;
							_renderDataBuffer.at((finalXPosition + objItr.get()->GetPosition().GetY()) + render_Y)
								.Char.UnicodeChar = objItr.get()->GetRenderData().at(globalCounter).Char.UnicodeChar;
							_renderDataBuffer.at((finalXPosition + objItr.get()->GetPosition().GetY()) + render_Y)
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

void Renderer::RenderText(const std::string text, const int Attributes, const Vector2D<int> position)
{
	COORD firstCell = { 0, 0 };
	int height = position.GetY() * _consoleScreenBufferInfo.dwSize.X;
	for (unsigned int i = 0; i < text.length(); i++)
	{
		_ASSERT_EXPR(text.length() < GetOverallBufferSize(), "RenderText overflow!\n"); //Should be an exception
		_renderDataBuffer.at((height + (position.GetX() - (text.length()/2))) + i).Char.AsciiChar = text.at(i);
		_renderDataBuffer.at((height + (position.GetX() - (text.length() / 2))) + i).Attributes = Attributes;
	}
}

