#include "Config.h"
//#include "Customer.h"

#ifndef _BASEDUINO_h
#define _BASEDUINO_h

class BaseDuino {
public:
	 BaseDuino();
	unsigned int _count = 0;
	//A=100:256;B=5:9;
	char RESET = 64; //@
	static String _txtContainer;
	char oinputKey;
	void parse(char inputKey);
	static void write(String _w);
};

#endif

