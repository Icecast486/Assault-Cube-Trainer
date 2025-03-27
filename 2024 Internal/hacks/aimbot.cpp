#include "aimbot.h"

#include <iostream>
#include <math.h>


#define PI 3.1415926535



/* Gets the viewangles of src to look at dst */
ViewAngles aimbot::getAngles(Vector3& src, Vector3& dst)
{
	ViewAngles angles;
	Vector3 delta = dst - src; /* makes the world relative to the src */
	float hypLen = sqrt((delta.x * delta.x) + (delta.y * delta.y) + (delta.z * delta.z));

	angles = ViewAngles();
	angles.pitch = asin(delta.z / hypLen) * 180 / PI;
	angles.yaw = (-atan2(delta.x, delta.y) * 180 / PI) + 180; /* +180 becase yaw in AS is 1-360 */

	return angles;
}



/* Gets the best target based on ditance */
Entity* aimbot::getBestTarget()
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
		float distanceFromPlayer;

		if (!currentEnt || currentEnt->bIsDead)
			continue;

		distanceFromPlayer = localPlayer->vPosition.get3DDistance(currentEnt->vPosition);

		if (distanceFromPlayer < tempDistanceFromPlayer || !closestEnt) {
			tempDistanceFromPlayer = distanceFromPlayer;
			closestEnt = currentEnt;
		}
	}

	return closestEnt;
}



/* This gets executed in a loop to trigger aimbot logic */
void aimbot::execute()
{
	if (!bIsActive)
		return;

	/* Checking to see if player is in a valid game */
	if (Engine::getEntityList() == nullptr)
		return;

	Entity* target = getBestTarget();

	if (target == nullptr)
		return;

	Engine::localPlayer->vViewAngles = getAngles(Engine::localPlayer->vHeadPos, target->vHeadPos);
}