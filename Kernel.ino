#include "Config.h";

UsbDuino *_b; //Altere para UsbDuino, EtheDuino ou WifliDuino


void setup() {
	SERIAL_DEBUG_SETUP(9600);
	DEBUG("Available memory", FREE_RAM);
	_b = new UsbDuino();
	_b->init();
	//_b->addSSID("SSID", "PASS"); //ONLY TO WifliDuino
	_b->Connect();
}

void loop() {
	_b->loop();
}