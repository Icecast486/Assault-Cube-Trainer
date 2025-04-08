#include "game.h"

void game::killEveryone()
{
	for (int index = 0; index < Engine::maxPlayers - 1; index++)
	{
		Entity* currentEnt = Engine::entityList->Entities[index];
		currentEnt->bIsDead = true;
	}
}