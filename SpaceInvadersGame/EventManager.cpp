#include "EventManager.h"
#include <algorithm>

bool EventManager::isAlreadyConstructed(false);

EventManager::EventManager()
{
	if (isAlreadyConstructed)
	{
		throw std::exception("EventManager already exists!\n");
	}
	isAlreadyConstructed = true;
}

EventManager::~EventManager()
{
	isAlreadyConstructed = false;
}

void EventManager::GetNextEvent()
{

}

void EventManager::Update()
{

}
