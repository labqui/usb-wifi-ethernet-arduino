#include "Config.h"

#ifndef _ETHEDUINO_h
#if TypeArduino == 2
#define _ETHEDUINO_h

#include <SPI.h>
#include <Ethernet.h>

class EtheDuino : public BaseDuino, public IDuino {
public:
	EtheDuino(char _ip[]);
	void init();
	static EthernetClient Client;
	void Connect();
	static void write(String _w);
	virtual void loop();
};
#endif
#endif

