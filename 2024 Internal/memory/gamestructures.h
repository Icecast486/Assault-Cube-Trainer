#pragma once

#include <iostream>

#include "vectors.h"

#ifndef GAMESTRUCTURES_H
#define GAMESTRUCTURES_H

class Entity
{
public:
	Vector3 vHeadPos; //0x0004
	char pad_0010[24]; //0x0010
	Vector3 vPosition; //0x0028
	ViewAngles vViewAngles; //0x0034
	float fForceView; //0x0040
	char pad_0044[50]; //0x0044
	bool bIsDead; //0x0076
	char pad_0077[97]; //0x0077
	void* pCurrentWeaponMaybe; //0x00D8
	char pad_00DC[16]; //0x00DC
	int32_t iHealth; //0x00EC
	char pad_00F0[277]; //0x00F0
	char pEntityName[16]; //0x0205
	char pad_0215[247]; //0x0215
	int32_t iTeamNum; //0x030C
	char pad_0310[80]; //0x0310
	void* pLastWeapon; //0x0360
	class Hand* pCurretnWeapon; //0x0364
	class Hand* pCurrentWeapon2; //0x0368
	char pad_036C[1864]; //0x036C

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0AB4

class EntityList
{
public:
	char pad_0000[4]; //0x0000
	class Entity* Entities[31]; //0x0004
}; //Size: 0x0080

class Weapons
{
public:
	int32_t mWeaponID; //0x0004
	class Entity* pWeaponOwner; //0x0008
	class WeaponData* pWeapon; //0x000C
	int32_t* pAmmo; //0x0010
	int32_t* pMag; //0x0014
	int32_t* pCooldown; //0x0018
	int32_t mIsShooting; //0x001C
	int32_t mIsReloading; //0x0020
	char pad_0024[16]; //0x0024

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0034

class WeaponData
{
public:
	char mWpnName[23]; //0x0000
	char mWpnDesc[43]; //0x0017
	int16_t mAtkSound; //0x0042
	int16_t mRldSound; //0x0044
	int16_t mRldDelay; //0x0046
	int16_t mAtkDelay; //0x0048
	int16_t mWpnDamage; //0x004A
	int16_t mWpnPushBack; //0x004C
	int16_t N000004BB; //0x004E
	int16_t N0000059D; //0x0050
	int16_t mWpnSpread; //0x0052
	int16_t mWpnKick; //0x0054
	int16_t mMagSize; //0x0056
	int16_t mWpnAnimKick; //0x0058
	int16_t mWpnAnimKickBack; //0x005A
	int16_t mIDK; //0x005C
	int16_t mIDK2; //0x005E
	int16_t mIDK3; //0x0060
	int16_t mIDK4; //0x0062
	int16_t mIDK5; //0x0064
	char pad_0066[4]; //0x0066
}; //Size: 0x006A

class Hand
{
public:
	char pad_0004[4]; //0x0004
	class Entity* pOwner; //0x0008
	class WeaponData* pWeaponData; //0x000C
	int32_t* pAmmo; //0x0010
	int32_t* pClip; //0x0014
	char pad_0018[3756]; //0x0018

	virtual void Function0() = 0;
	virtual void Function1() = 0;
	virtual void Function2() = 0;
	virtual void Function3() = 0;
	virtual void Function4() = 0;
	virtual void Function5() = 0;
	virtual void Function6() = 0;
	virtual void Function7() = 0;
	virtual void Function8() = 0;
	virtual void Function9() = 0;
}; //Size: 0x0EC4

#endif // GAMESTRUCTURES_H