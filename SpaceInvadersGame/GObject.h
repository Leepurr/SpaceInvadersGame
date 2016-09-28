#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>

template<class Type>
class Vector2D;

enum class Etype
{
	Standard = 0,
	Player,
	Enemy
};

class GObject
{
public:
	virtual const std::vector<CHAR_INFO>& GetRenderData() const = 0;
	virtual void Update() = 0;
	virtual void Load() = 0;
	virtual const Etype GetObjectType() const = 0;
	virtual const std::string GetObjectID() = 0;
	virtual const Vector2D<int> GetPosition() const = 0;
	virtual const std::string GetObjectName() const = 0;
	virtual const Vector2D<int> GetSize() const = 0;
	virtual void SetPosition(const Vector2D<int> newPosition) = 0;
};