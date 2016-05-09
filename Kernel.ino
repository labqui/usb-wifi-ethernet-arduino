#include "Config.h";

UsbDuino *_b;


void setup() {
	SERIAL_DEBUG_SETUP(9600);
	DEBUG("Available memory", FREE_RAM);
	_b = new UsbDuino();
	_b->init();
	//_b->addSSID("SSID", "PASS"); //ONLY TO Wifly
	_b->Connect();
}

void loop() {
	_b->loop();
}