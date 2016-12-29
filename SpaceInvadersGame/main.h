#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>
#include <string>
#include <memory>
#include "Game.h"

HANDLE g_stdInputHandle;
HANDLE g_stdOutputHandle;
HANDLE g_stdErrorHandle;
HWND g_consoleWindow;
HWND g_desktopScreen;
int g_screenWidth;
int g_screenHeight;
SMALL_RECT g_consoleScreenBufferRect;
RECT g_consoleWindowSizeRect;
RECT g_desktopResolutionRect;
COORD g_consoleScreenBufferSize;
std::vector<CHAR_INFO> g_lpBuffer;
CONSOLE_CURSOR_INFO g_consoleCursorInfo;
CONSOLE_SCREEN_BUFFER_INFO g_consoleScreenBufferInfo;
Game g_Game;
bool isRunning;
LARGE_INTEGER Frequency, Tick, Tock;
double secondsPassed, SecondsPerTick;
std::string timePassed;

BOOL CtrlHandler(DWORD fdwCtrlType);
inline bool Startup(const int cols, const int rows);

//Debug methods
void Render();
void RenderDebugText(std::string text, int Attributes, int position);
