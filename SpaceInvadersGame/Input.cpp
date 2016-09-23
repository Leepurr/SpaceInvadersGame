#include "Input.h"

const bool Input::isKeyDown(const int vKey) const
{
	if (GetAsyncKeyState(vKey)& 0x8000)
	{
		return true;
	}
	return false;
}