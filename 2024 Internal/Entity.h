#pragma once

#include <iostream>

#include "Vectors.h"

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
	char pad_0000[4]; //0x0000
	Vector3 mHeadPos; //0x0004
	char pad_0010[24]; //0x0010
	Vector3 mPos; //0x0028
	Vector3 mViewAngles; //0x0034
	char pad_0040[172]; //0x0040
	int32_t mHeatlh; //0x00EC
	char pad_00F0[104]; //0x00F0
}; //Size: 0x0158

#endif