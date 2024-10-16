#include "pch.h"
#include "aimbot.h"

#include <iostream>
#include <math.h>


#define PI 3.1415926535


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
	Entity* closestEnt = entityList->Entities[0];

	if (closestEnt == nullptr)
		return nullptr;

	float tempDistanceFromPlayer = localPlayer->mPos.get3DDistance(closestEnt->mPos);
	int maxPlayers = Engine::getMaxPlayers();

	for (int index = 0; index < maxPlayers - 1; index++)
	{
		Entity* currentEnt = entityList->Entities[index];
		float distanceFromPlayer = localPlayer->mPos.get3DDistance(currentEnt->mPos);

		std::cout << "INDEX " << index << std::endl;

		if (currentEnt->mHealth <= 0)
			continue;

		if (distanceFromPlayer < tempDistanceFromPlayer)
		{
			tempDistanceFromPlayer = distanceFromPlayer;
			closestEnt = currentEnt;
		}

	}

	return closestEnt;
}


void Aimbot::execute() 
{
	Entity* localPlayer = Engine::getLocalPlayer();
	Entity* target = getBestTarget();

	if (target == nullptr)
		return;

	localPlayer->mViewAngles = getAngles(localPlayer->mHeadPos, target->mHeadPos);
}

