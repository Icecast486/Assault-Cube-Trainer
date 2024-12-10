#ifndef AIMBOT_H
#define AIMBOT_H

#include "../memory/vectors.h"
#include "../interface/engine.h"
#include "hack.h"

class Aimbot : public Hack
{
public:
	Aimbot();
	Aimbot(bool isActive);
	ViewAngles getAngles(Vector3& src, Vector3& dst);
	Entity* getBestTarget();
	void execute();
};

#endif !AIMBOT_H
