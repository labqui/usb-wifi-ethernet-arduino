#define TypeArduino 1 // 1-USB ; 2-Ethernet ; 3-WiFly
#define ModoStreaming //CONEXÃO DIRETA OU COMENTE PARA USAR A URL COMO COMANDOS
#define SERIAL_DEBUG false

#ifndef _CONFIG_h
#define _CONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SerialDebug.h>

#include "BaseDuino.h"
#include "IDuino.h"

#if TypeArduino == 1
#include "UsbDuino.h"
#endif

#if TypeArduino == 2
#include "EtheDuino.h"
#endif

#if TypeArduino == 3
#include "WiFiDuino.h"
#endif

#include "Customer.h"

class Config {
public:
	static char IP[];
	static int Port;
};

#endif

