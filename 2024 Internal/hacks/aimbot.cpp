#include "aimbot.h"

#include <iostream>
#include <math.h>


#define PI 3.1415926535

Aimbot::Aimbot() : Hack(false) { }
Aimbot::Aimbot(bool isActive) : Hack(true) { }

ViewAngles Aimbot::getAngles(Vector3& src, Vector3& dst)
{
	ViewAngles angles;
	Vector3 delta = dst - src; /* makes the world relative to the src */
	float hypLen = sqrt((delta.x * delta.x) + (delta.y * delta.y) + (delta.z * delta.z));

	angles = ViewAngles();
	angles.pitch = asin(delta.z / hypLen) * 180/PI;
	angles.yaw = (-atan2(delta.x, delta.y) * 180 / PI) + 180;

	return angles;
}


/* should return the closest entity to player */
Entity* Aimbot::getBestTarget()
{
	EntityList* entityList = Engine::getEntityList();
	Entity* localPlayer = Engine::getLocalPlayer();
	Entity* closestEnt = nullptr;

	float tempDistanceFromPlayer = -1.0f;
	int maxPlayers = Engine::getMaxPlayers();

	/* -1 because server counts lp as a player and lp isnt in the ent list */
	for (int index = 0; index < maxPlayers - 1; index++)
	{
		Entity* currentEnt = entityList->Entities[index];
		// localPlayer->iTeamNum == currentEnt->iTeamNum
		if (!currentEnt || currentEnt->bIsDead)
			continue;

		float distanceFromPlayer = localPlayer->vPosition.get3DDistance(currentEnt->vPosition);

		if (distanceFromPlayer < tempDistanceFromPlayer || !closestEnt)
		{
			tempDistanceFromPlayer = distanceFromPlayer;
			closestEnt = currentEnt;
		}
	}
	
	return closestEnt;
}


void Aimbot::execute() 
{
	if (!isActive())
		return;

	/* Checking to see if player is in a valid game */
	if (Engine::getEntityList() == nullptr)
		return;

	Entity* localPlayer = Engine::getLocalPlayer();
	Entity* target = getBestTarget();

	if (target == nullptr)
		return;

	localPlayer->vViewAngles = getAngles(localPlayer->vHeadPos, target->vHeadPos);
}

