#pragma once

#include <iostream>

#include "vectors.h"

#ifndef GAMESTRUCTURES_H
#define GAMESTRUCTURES_H

class Entity
{
public:
	char pad_0000[4]; //0x0000
	Vector3 mHeadPos; //0x0004
	char pad_0010[24]; //0x0010
	Vector3 mPos; //0x0028
	ViewAngles mViewAngles; //0x0034
	char pad_0040[172]; //0x0040
	int32_t mHealth; //0x00EC
	char pad_00F0[44]; //0x00F0
	int32_t mCurrentWeaponReserve; //0x011C
	char pad_0120[8]; //0x0120
	int32_t mMaybeTeamNum; //0x0128
	char pad_012C[20]; //0x012C
	int32_t mCurrentWeaponAmmo; //0x0140
	char pad_0144[193]; //0x0144
	char mEntityName[16]; //0x0205
	char pad_0215[101]; //0x0215
}; //Size: 0x027A



class EntityList
{
public:
	char pad_0000[4]; //0x0000
	class Entity* Entities[31]; //0x0004 Each element is an entity pointer 
}; //Size: 0x0080

#endif