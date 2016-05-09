#include "WiFiDuino.h"

#if TypeArduino == 3

WiFlyServer server(Config::Port);

int issid = 0;
int rowIndex = 0;
int colCount = 2;
int rowCount = 3;

WiFiDuino::WiFiDuino(char _ip[]) {
	IPAddress ip(_ip[0], _ip[1], _ip[2], _ip[3]);

};

void WiFiDuino::init() {

	ssids = new char*[rowCount];
	passw = new char*[rowCount];

	for (int k = 0; k < rowCount; ++k) {
		ssids[k] = new char[colCount];
		passw[k] = new char[colCount];
	}

};

void WiFiDuino::Connect() {
	WiFly.begin();
	delay(1000);
	DEBUG("rowIndex", rowIndex);
	if (rowIndex == 0) {
	DEBUG("WiFiDuino->Connect", "Use the method ->addSSID(\"SSID\", \"PASS\") antes do ->Connect()");
	while(1){}
}

	if (issid >= rowIndex)
		issid = 0;

	if (!WiFly.join(ssids[issid], passw[issid])) {
		DEBUG("Falha ao conectar", ssids[issid]);
		issid++;
		this->Connect();
		return;
	}
	else {
		DEBUG("Conectado", ssids[issid]);
	}
	server.begin();
	DEBUG("IP", WiFly.ip());
}

void  WiFiDuino::addSSID(char _ssid[], char _passw[]) {

	ssids[rowIndex] = _ssid;
	passw[rowIndex] = _passw;
	rowIndex++;
}

void WiFiDuino::loop() {

	WiFlyClient _client = server.available();

	if (!_client) {
		delay(500); 
	} else {
			while (_client.connected()) {
				char oinputKey;
				while (_client.available()) {
					char inputKey = _client.read();		
					if (inputKey == 69) { //E
						const char *_output = BaseDuino::_txtContainer.c_str();
						_client.write((uint8_t*)_output, strlen(_output));
						//BaseDuino::_txtContainer = "";
						break;
					}

					this->parse(inputKey);
				}
				
			}
	}
};
#endif
