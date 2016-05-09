#ifndef ENGINE_H
#define ENGINE_H

#include "Config.h"

class Engine {
public:
	Engine(int baut);
	int static freeRam();
	bool check();
};

#endif
