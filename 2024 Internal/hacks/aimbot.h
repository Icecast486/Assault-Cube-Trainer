#ifndef AIMBOT_H
#define AIMBOT_H

#include "../memory/vectors.h"
#include "../interface/engine.h"

namespace aimbot
{
	inline bool bIsActive;

	ViewAngles getAngles(Vector3& src, Vector3& dst);
	Entity* getBestTarget();
	void execute();
}

#endif !AIMBOT_H
