#include "Customer.h"

void Customer::init() {

	pinMode(A0, INPUT);
	pinMode(3, OUTPUT);
	DEBUG("Customer->init", "Config Pins OK");
}


bool Customer::execStream(int _class, char _p[]) {
	if (_class == 65) {
		BaseDuino::_txtContainer = String(analogRead(A0), DEC);
	}
	else if (_class == 66) {
		analogWrite(3, atoi(_p));
		BaseDuino::_txtContainer = _p;
	}
	else if (_class == 67) {
		analogWrite(3, atoi(_p));
		BaseDuino::_txtContainer = _p;
	}
	else if (_class == 68) {
	}
	return true;
}

/*
instructions: http://www.noip.com/pt-BR/integrate/request
*/

void URLInitial(BaseDuino _c) {
//class init do processo customer

//#ifdef ServerDEBUG
//	Serial.println("URLInitial: Call");
//#endif
//	_c.Client.stop();
//	char server[] = "dynupdate.no-ip.com";
//	if (_c.Client.connect(server, 80)) {
//#ifdef ServerDEBUG
//		Serial.println("Connecting...");
//#endif
//		_c.Client.println("GET /nic/update?hostname=YOUR_NO_IP_DOMAIN&myip=YOUR_IP_HERE HTTP/1.1");
//		_c.Client.println("Host: dynupdate.no-ip.com");
//		_c.Client.println("Authorization: Basic YOUR_LOGIN_NO_IP:YOUR_PASSWORD_BASE64");
//		_c.Client.println("User-Agent: ClientGitHubArduinoLabQuiMod/1.0 YOUR_EMAIL_HERE");
//		_c.Client.println("Connection: close");
//		_c.Client.println();
//
//#ifdef ServerDEBUG
//		Serial.println("URLInitial: no-ip updated");
//#endif
//	}
//	else {
//#ifdef ServerDEBUG
//		Serial.println("URLInitial: Um erro ocorreu!");
//#endif
//}
}

