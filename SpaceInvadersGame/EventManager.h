#pragma once

class EventManager
{
private: 
	static bool isAlreadyConstructed;
public:
	explicit EventManager();
	~EventManager();
	void GetNextEvent();
	void Update();
};