#pragma once
#include "main.h"
#include <iostream>

int wmain(int argc, wchar_t* argv[])
{
	Startup();
	//Load scoreboard
	g_Game.Start();
	g_Game.Load();
	g_Game.Update();
	g_Game.Render();
//	Render();
	int a = 0;
	std::cin >> a;
	return 0;
}

void Render()
{
	COORD firstCell = { 0, 0 };
	for (CHAR_INFO& itr : lpBuffer)
	{
		itr.Attributes = BACKGROUND_BLUE + FOREGROUND_GREEN;
		itr.Char.UnicodeChar = 'F';
		itr.Char.AsciiChar = 'F';
	}
	WriteConsoleOutput(stdOutputHandle, lpBuffer.data(), consoleScreenBufferSize, firstCell, &consoleScreenBufferRect);
}

void Update()
{

}

inline void Startup()
{
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	stdErrorHandle = GetStdHandle(STD_ERROR_HANDLE);
	stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	stdInputHandle = GetStdHandle(STD_INPUT_HANDLE);
	ConsoleWindow = GetConsoleWindow();
	DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
	DWORD dwShareMode = 0;
	if ((stdOutputHandle = CreateConsoleScreenBuffer(dwDesiredAccess, dwShareMode, NULL, CONSOLE_TEXTMODE_BUFFER, NULL)) != INVALID_HANDLE_VALUE)
	{
		if (!SetConsoleActiveScreenBuffer(stdOutputHandle))
		{
			std::cout << "Coudldn't Activate new screen buffer." << std::endl;
		}
	}
	else
	{
		std::cout << "Error: " << GetLastError() << std::endl;
	}
	stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleScreenBufferSize.X = 80;
	consoleScreenBufferSize.Y = 25;
	consoleScreenBufferRect.Left = 0;							//The x-coordinate of the upper left corner of the rectangle.
	consoleScreenBufferRect.Top = 0;							//The y-coordinate of the upper left corner of the rectangle.
	consoleScreenBufferRect.Right = (consoleScreenBufferSize.X - 1);  //The x-coordinate of the lower right corner of the rectangle.
	consoleScreenBufferRect.Bottom = (consoleScreenBufferSize.Y - 1); //The y-coordinate of the lower right corner of the rectangle.
	RetryConsoleBuffer:
	if (SetConsoleScreenBufferSize(stdOutputHandle, consoleScreenBufferSize) == 0)
	{
		std::cout << "Failed to set new screen buffer size. " << GetLastError() << std::endl;
	}

	//SetConsoleScreenBufferInfoEx()
	if (SetConsoleWindowInfo(stdOutputHandle, TRUE, &consoleScreenBufferRect) == 0)
	{
		goto RetryConsoleBuffer;
		std::cout << "Failed to set new window size." << GetLastError() << std::endl;
	}
	if (!SetConsoleActiveScreenBuffer(stdOutputHandle))
	{
		std::cout << "Coudldn't Activate new screen buffer." << std::endl;
	}
	GetConsoleScreenBufferInfo(stdOutputHandle, &consoleScreenBufferInfo);

	RECT windowSize;
	RECT DesktopResolutionRect;
	HWND DesktopScreen = GetDesktopWindow();
	ConsoleWindow = GetConsoleWindow();
	GetWindowRect(DesktopScreen, &DesktopResolutionRect);
	GetWindowRect(ConsoleWindow, &windowSize);
	int width = windowSize.right - windowSize.left;
	int height = windowSize.bottom - windowSize.top;
	int PositionX = ((DesktopResolutionRect.right - DesktopResolutionRect.left) / 2 - width / 2);
	int PositionY = ((DesktopResolutionRect.bottom - DesktopResolutionRect.top) / 2 - height / 2);

	SetWindowPos(ConsoleWindow, NULL, PositionX, PositionY, width, height, SWP_NOZORDER | SWP_NOSIZE);
	lpBuffer.resize((consoleScreenBufferSize.X * consoleScreenBufferSize.Y));
}
