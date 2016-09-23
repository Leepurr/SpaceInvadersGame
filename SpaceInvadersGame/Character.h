#pragma once
#include "GObject.h"
#include "Vector.h"

class Character : public GObject
{
protected:
	std::string _Name;
	std::string _ID;
	Vector2D _position;
	Etype mType = Etype::Player;
	int m_width = 0;
	int m_height = 0;
	std::vector<CHAR_INFO> chRenderData;
public:
	virtual const std::vector<CHAR_INFO>& GetRenderData() const;
	virtual void Update();
	virtual void Load();
	virtual const Etype GetObjectType() const;
	virtual const std::string GetObjectID();
	virtual const Vector2D GetPosition() const;
	virtual const std::string GetObjectName() const;
	virtual const Vector2D GetSize() const;
	virtual void SetPosition(const Vector2D newPosition);
};