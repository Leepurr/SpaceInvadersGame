#pragma once
#include "main.h"
#include <iostream>
#include "Datatypes.h"

long long milliseconds_now()
{
	static LARGE_INTEGER s_frequency;
	static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
	if (s_use_qpc)
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return (1000LL * now.QuadPart) / s_frequency.QuadPart;
	}
	else
	{
		return GetTickCount();
	}
}

int wmain(int argc, wchar_t* argv[])
{
	isRunning = false;
	secondsPassed, SecondsPerTick = 0;
	if (Startup(80, 25))
	{
		g_Game.Start();
		//TODO: Load scoreboard
		g_Game.Load();
		isRunning = true;
		QueryPerformanceFrequency(&Frequency);
		SecondsPerTick = (1.0 / (double)Frequency.QuadPart);
		QueryPerformanceCounter(&Tick);
		if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
		{
			while (isRunning)
			{
				isRunning = !g_Game.isQuitRequested();
				QueryPerformanceCounter(&Tock);
				g_Game.Update();
				g_Game.Render();
				LONGLONG interval = (Tock.QuadPart - Tick.QuadPart);
				secondsPassed = ((double)interval * SecondsPerTick);
				QueryPerformanceCounter(&Tick);
				Sleep(10);
			}
		}
	}
	else
	{
		std::cout << "Couldn't start the game!\n" << std::endl;
	}
	return 0;
}

void Render()
{
	COORD firstCell = { 0, 0 };
	for (CHAR_INFO& itr : g_lpBuffer)
	{
		itr.Attributes = BACKGROUND_BLUE + FOREGROUND_GREEN;
		itr.Char.UnicodeChar = 'F';
		itr.Char.AsciiChar = 'F';
	}
	WriteConsoleOutput(g_stdOutputHandle, g_lpBuffer.data(), g_consoleScreenBufferSize, firstCell, &g_consoleScreenBufferRect);
}

void RenderDebugText(std::string text, int Attributes, int position)
{
	COORD firstCell = { 0, 0 };
	for (unsigned int i = 0; i < text.length(); i++)
	{
		g_lpBuffer.at(position + i).Char.AsciiChar = text.at(i);
		g_lpBuffer.at(i).Attributes = Attributes;
	}
	WriteConsoleOutput(g_stdOutputHandle, g_lpBuffer.data(), g_consoleScreenBufferSize, firstCell, &g_consoleScreenBufferRect);
}

BOOL CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
		// Handle the CTRL-C signal. 
	case CTRL_C_EVENT:
		printf("Ctrl-C event\n\n");
		Beep(750, 300);
		return(TRUE);

		// CTRL-CLOSE: confirm that the user wants to exit. 
	case CTRL_CLOSE_EVENT:
		isRunning = false;

		Beep(50, 200);
		return(TRUE);
	}
	return(FALSE);
}

inline bool Startup(const int cols, const int rows)
{
	bool status = true;
	if (g_screenWidth = GetSystemMetrics(SM_CXSCREEN) == 0) { status = false; };
	if (g_screenHeight = GetSystemMetrics(SM_CYSCREEN) == 0) { status = false; };
	if ((g_stdErrorHandle = GetStdHandle(STD_ERROR_HANDLE)) == 0) { status = false; };
	if ((g_stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE)) == 0) { status = false; };
	if ((g_stdInputHandle = GetStdHandle(STD_INPUT_HANDLE)) == 0) { status = false; };
	if ((g_consoleWindow = GetConsoleWindow()) == 0) { status = false; };
	DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
	DWORD dwShareMode = 0;
	if ((g_stdOutputHandle = CreateConsoleScreenBuffer(dwDesiredAccess, dwShareMode, NULL, CONSOLE_TEXTMODE_BUFFER, NULL)) != INVALID_HANDLE_VALUE)
	{
		if (!SetConsoleActiveScreenBuffer(g_stdOutputHandle))
		{
			status = false;
			std::cout << "Coudldn't Activate new screen buffer." << std::endl;
		}
	}
	else
	{
		status = false;
		std::cout << "Error: " << GetLastError() << std::endl;
	}
	if((g_stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE)) == 0) { status = false; };
	g_consoleScreenBufferSize.X = cols;
	g_consoleScreenBufferSize.Y = rows;
	g_consoleScreenBufferRect.Left = 0;										//The x-coordinate of the upper left corner of the rectangle.
	g_consoleScreenBufferRect.Top = 0;										//The y-coordinate of the upper left corner of the rectangle.
	g_consoleScreenBufferRect.Right = (g_consoleScreenBufferSize.X - 1);	//The x-coordinate of the lower right corner of the rectangle.
	g_consoleScreenBufferRect.Bottom = (g_consoleScreenBufferSize.Y - 1);	//The y-coordinate of the lower right corner of the rectangle.
	unsigned int SetBufferAttempt = 0;
	bool failedSettingBuffer = false;
RETRYSETTINGBUFFER:
	if (SetConsoleScreenBufferSize(g_stdOutputHandle, g_consoleScreenBufferSize) == 0)
	{
		failedSettingBuffer = true;
		status = false;
		std::cout << "Failed to set new screen buffer size. " << GetLastError() << std::endl;
	}
	else
	{
		std::cout << "Re-attempt to set Screen Buffer Size after window resize was sucessful!\n";
		failedSettingBuffer = false;
		status = true;
	}

	if (SetConsoleWindowInfo(g_stdOutputHandle, TRUE, &g_consoleScreenBufferRect) == 0)
	{
		status = false;
		std::cout << "Failed to set new window size." << GetLastError() << std::endl;
	}

	SetBufferAttempt++;
	if (failedSettingBuffer &&(SetBufferAttempt <= 1))
	{
		goto RETRYSETTINGBUFFER;
	}
	if (!SetConsoleActiveScreenBuffer(g_stdOutputHandle))
	{
		status = false;
		std::cout << "Coudldn't Activate new screen buffer." << std::endl;
	}
	if((GetConsoleScreenBufferInfo(g_stdOutputHandle, &g_consoleScreenBufferInfo)) == 0) { status = false; };

	
	if((g_desktopScreen = GetDesktopWindow()) == 0) { status = false; };
	if((g_consoleWindow = GetConsoleWindow()) == 0) { status = false; };
	if((GetWindowRect(g_desktopScreen, &g_desktopResolutionRect)) == 0) { status = false; };
	if((GetWindowRect(g_consoleWindow, &g_consoleWindowSizeRect)) == 0) { status = false; };
	int width = g_consoleWindowSizeRect.right - g_consoleWindowSizeRect.left;
	int height = g_consoleWindowSizeRect.bottom - g_consoleWindowSizeRect.top;
	int PositionX = ((g_desktopResolutionRect.right - g_desktopResolutionRect.left) / 2 - width / 2);
	int PositionY = ((g_desktopResolutionRect.bottom - g_desktopResolutionRect.top) / 2 - height / 2);

	if((SetWindowPos(g_consoleWindow, NULL, PositionX, PositionY, width, height, SWP_NOZORDER | SWP_NOSIZE)) == 0) { status = false; };
	g_consoleCursorInfo.dwSize = 100;
	g_consoleCursorInfo.bVisible = FALSE;
	if (SetConsoleCursorInfo(g_stdOutputHandle, &g_consoleCursorInfo) == 0) { status = false; };
	g_lpBuffer.resize((g_consoleScreenBufferSize.X * g_consoleScreenBufferSize.Y));
	return status;
}