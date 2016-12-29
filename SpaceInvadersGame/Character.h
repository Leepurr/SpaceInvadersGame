#pragma once
#include "GObject.h"
#include "Vector.h"

class Character : public GObject
{
protected:
	int m_width = 0;
	int m_height = 0;
	Vector2D<int> _position;
	Etype mType = Etype::Player;
	std::string _Name;
	std::string _ID;
	std::vector<CHAR_INFO> chRenderData;
public:
	virtual const std::vector<CHAR_INFO>& GetRenderData() const;
	virtual void Update();
	virtual void Load();
	virtual const Etype GetObjectType() const;
	virtual const std::string GetObjectID();
	virtual const Vector2D<int> GetPosition() const;
	virtual const std::string GetObjectName() const;
	virtual const Vector2D<int> GetSize() const;
	virtual void SetPosition(const Vector2D<int> newPosition);
};