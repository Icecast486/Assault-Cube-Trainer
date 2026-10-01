#ifndef AIMBOT_H
#define AIMBOT_H

#include "../../math/math.hpp"
#include "../../game/structures.h"

namespace aimbot
{
	inline bool bIsActive;

	ViewAngles get_angles(Vector3& src, Vector3& dst);
	Entity* get_best_target();
	void execute();
}

#endif !AIMBOT_H