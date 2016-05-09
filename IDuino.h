#include "Config.h"

#ifndef _IDUINO_h
#define _IDUINO_h

class IDuino
{
public:
	virtual void init() = 0;
	void write(String _w);
};

#endif

