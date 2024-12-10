#include "hack.h"

Hack::Hack() : mIsActive(false) { }
Hack::Hack(bool isActive) : mIsActive(isActive) { } 
Hack::~Hack() {}


bool Hack::isActive()
{
	return mIsActive;
}



void Hack::activate()
{
	mIsActive = true;
}



void Hack::deactivate()
{
	mIsActive = false;
}



void Hack::toggle()
{
	if (mIsActive)
	{
		mIsActive = !mIsActive;
		return;
	}

	mIsActive = true;
}