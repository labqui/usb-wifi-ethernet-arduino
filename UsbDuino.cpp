#include "UsbDuino.h"

#if TypeArduino == 1 

UsbDuino::UsbDuino() {
	DEBUG("USB", "Init");
}

void UsbDuino::init() {};

void UsbDuino::Connect() {
#if SERIAL_DEBUG
	DEBUG("Error", "SERIAL_DEBUG can not be true, change to false");
#else
	Serial.begin(9600);
	DEBUG("Connect", "Ok");
#endif
}


void UsbDuino::loop() {
		char oinputKey;
			while (Serial.available()) {
				char inputKey = (char)Serial.read();
				Serial.println(inputKey);
				if (inputKey == 69) { //E
					const char *_output = BaseDuino::_txtContainer.c_str();
					Serial.write((uint8_t*)_output, strlen(_output));
					DEBUG("Write", BaseDuino::_txtContainer);
					BaseDuino::_txtContainer = "";
					break;
				}

				this->parse(inputKey);
			}

};
#endif


