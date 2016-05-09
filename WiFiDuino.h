#include "Config.h"

#ifndef _WIFIDUINO_h 
#if TypeArduino == 3
#define _WIFIDUINO_h 

#include <SPI.h>
#include <WiFly.h>

class WiFiDuino : public BaseDuino, public IDuino {
public:
	WiFiDuino(char _ip[]);
	char** ssids;
	char** passw;
	void init();
	void Connect();
	void addSSID(char ssid[], char passw[]);
	static void write(String _w);
	virtual void loop();
};

#endif
#endif

