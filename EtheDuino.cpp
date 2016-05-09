#include "EtheDuino.h"

#if TypeArduino == 2

EthernetServer server(Config::Port);

EthernetClient EtheDuino::Client = EthernetClient();

IPAddress ip;

EtheDuino::EtheDuino(char _ip[]) {
	DEBUG("Ethernet", "Init");
	IPAddress ipc(_ip[0], _ip[1], _ip[2], _ip[3]);
	ip = ipc;
};

void EtheDuino::init() {};

void EtheDuino::Connect() {
	byte mac[] = {
		0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
	};
	Ethernet.begin(mac, ip);

	server.begin();

	DEBUG("IP", Ethernet.localIP());

}


void EtheDuino::loop() {

	EthernetClient _client = server.available();

	if (!_client) {
		delay(500);
	}
	else {
		while (_client.connected()) {
			char oinputKey;
			while (_client.available()) {
				char inputKey = _client.read();
				if (inputKey == 69) { //E
					const char *_output = BaseDuino::_txtContainer.c_str();
					_client.write((uint8_t*)_output, 4);
					BaseDuino::_txtContainer = "";
					break;
				}

				this->parse(inputKey);
			}

		}
	}
};
#endif


