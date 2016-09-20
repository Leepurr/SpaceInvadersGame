#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>

HANDLE stdInputHandle;
HANDLE stdOutputHandle;
HANDLE stdErrorHandle;
HWND ConsoleWindow;
int screenWidth;
int screenHeight;
//HANDLE consoleScreenBuffer;
SMALL_RECT consoleScreenBufferRect;
COORD consoleScreenBufferSize;
std::vector<CHAR_INFO> lpBuffer;
CONSOLE_SCREEN_BUFFER_INFOEX consoleScreenBufferInfoEx;
CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;

void Render();
void Update();