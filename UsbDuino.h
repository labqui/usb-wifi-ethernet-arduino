#include "Config.h"

#ifndef _USBDUINO_h
#if TypeArduino == 1
#define _USBDUINO_h 

class UsbDuino : public BaseDuino, public IDuino {
public:
	UsbDuino();
	void init();
	void Connect();
	static void write(String _w);
	virtual void loop();
};

#endif
#endif
