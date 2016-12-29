#include "Character.h"

const std::vector<CHAR_INFO>& Character::GetRenderData() const
{
	return chRenderData;
}

void Character::Update()
{
}

void Character::Load()
{
	_Name = "Character";
	_ID = "1";
	mType = Etype::Player;
	m_width = 5;
	m_height = 2;
	int i = 0;
	int j = 0;
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 5; j++)
		{
			CHAR_INFO temp;
			temp.Char.AsciiChar = ' ';
			temp.Char.UnicodeChar = ' ';
			temp.Attributes = BACKGROUND_BLUE + BACKGROUND_GREEN + BACKGROUND_RED + BACKGROUND_INTENSITY +
				FOREGROUND_BLUE + FOREGROUND_GREEN + FOREGROUND_RED + FOREGROUND_INTENSITY;
			chRenderData.push_back(temp);
		}
	}
	_position.SetVector2D(60, 20);
}

const Etype Character::GetObjectType() const
{
	return mType;
}

const std::string Character::GetObjectID()
{
	return _ID;
}

const Vector2D<int> Character::GetPosition() const
{
	return _position.GetVector();
}

const std::string Character::GetObjectName() const
{
	return _Name;
}

void Character::SetPosition(const Vector2D<int> newPosition)
{
	_position = newPosition;
}

const Vector2D<int> Character::GetSize() const
{
	return Vector2D<int>(m_height, m_width);
}
