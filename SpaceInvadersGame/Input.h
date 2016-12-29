#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class Input
{
public:
	Input(void) = default;
	~Input(void) = default;
	const bool isKeyDown(const int vKey) const;

};

