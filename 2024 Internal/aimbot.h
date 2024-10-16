#pragma once

#include "vectors.h"

namespace Aimbot
{
	ViewAngles getAngles(Vector3& src, Vector3& dst);
	Entity* getBestTarget();
	void execute();
}