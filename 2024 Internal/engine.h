#pragma once

#include <iostream>

#include "gamestructures.h"
#include "globals.h"

#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
public:
	static void initializeEngine();
	static Entity* getLocalPlayer();
	static EntityList* getEntityList();
	static int getMaxPlayers();
};

#endif