#pragma once
#include "Vector.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>

class SceneManager;

class Renderer
{
private:
	HANDLE _stdOutputHandle;
	std::vector<CHAR_INFO> _renderDataBuffer;
	CONSOLE_SCREEN_BUFFER_INFO _consoleScreenBufferInfo;
	SMALL_RECT _renderRegion;
	int render_X, render_Y;
	void ClearRenderBuffer();
public:
	Renderer(void) = default;
	~Renderer(void) = default;
	void Initialse(const int backgroundAttributes);
	void Render(void);
	void Update(SceneManager* sceneManager);
	const size_t GetOverallBufferSize() const { return _renderDataBuffer.size(); }
	const COORD GetRenderBufferSize() const { return _consoleScreenBufferInfo.dwSize; };
	void RenderText(const std::string text, const int Attributes, const Vector2D position);
};

