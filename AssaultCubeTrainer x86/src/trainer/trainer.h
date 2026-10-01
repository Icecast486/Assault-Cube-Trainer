#pragma once

#ifndef TRAINER_H
#define TRAINER_H

#include <windows.h>
#include <iostream>

namespace trainer {
	//inline uintptr_t module_base;

	void setup_trainer(HMODULE module);
	void initialize_trainer();
	bool initialize_hooks();
}

#endif