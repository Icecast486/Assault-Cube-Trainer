#include <iostream>
#include <stdexcept>

#include "pch.h"
#include "engine.h"
#include "offsets.h"


uintptr_t moduleBase;


void Engine::initializeEngine()
{
	moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");

	if (moduleBase == NULL)
		std::cout << "Module base is null!" << std::endl;
}


Entity* Engine::getLocalPlayer()
{
	Entity* localEnt = *(Entity**)(moduleBase + OFFSET_LOCALENT);

	if (localEnt == nullptr)
		return nullptr;

	return localEnt;
}


int Engine::getMaxPlayers()
{
	int localEnt = *(int*)(moduleBase + OFFSET_MAXPLAYERS);

	return localEnt;
}


EntityList* Engine::getEntityList()
{
	EntityList* entList = *(EntityList**)(moduleBase + OFFSET_ENTLIST);

	if (entList == nullptr)
		return nullptr;

	return entList;
}