#pragma once

#ifndef HACK_H
#define HACK_H

class Hack
{
public:
	Hack();
	Hack(bool active);

	virtual bool isActive();

	virtual void activate();
	virtual void deactivate();
	virtual void toggle();

	~Hack();

protected:
	bool mIsActive;
};

#endif // !HACK_H
