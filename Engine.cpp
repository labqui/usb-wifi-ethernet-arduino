#include "Engine.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEC };

Customer *_customer = new Customer();



#ifdef ModoEthernet
EthernetServer server(Config::Port);
EthernetClient Client;
#else
//WiFlyServer server(Config::Port);
//WiFlyClient Client;
#endif


unsigned int requestNumber = 0;

Engine::Engine(int baut) {
	Serial.begin(baut);
	// disable w5100 SPI while starting SD
	//digitalWrite(10, HIGH);
	//Verifica se existe SD: SD.begin(4)
	IPAddress ip(Config::IP[0], Config::IP[1], Config::IP[2], Config::IP[3]);
#ifdef ModoEthernet
	Serial.println("Modo Ethernet");
	Ethernet.begin(mac, ip);
#else
	Serial.println("Modo WiFly");
	WiFly.begin();

	char passphrase[] = "90rosas90";
	char ssid[] = "Rosas";

	if (!WiFly.join(ssid, passphrase)) {
	//if(!WiFly.createAdHocNetwork("myssid")){
		while (1) {
#ifdef ServerDEBUG
			Serial.println("Falha ao conectar");
#endif
		}
	}
	else {
#ifdef ServerDEBUG
		Serial.println("Conected");
#endif
	}
#endif
	delay(2000);
	server.begin();

	_customer->URLInitial(Client);

#ifdef ServerDEBUG
	//if (SD.begin(4)) { Serial.println("MicroSD localizado!"); }
	Serial.print("IP: ");
#ifdef ModoEthernet
	Serial.println(Ethernet.localIP());
#else
	Serial.println(WiFly.ip());
#endif



#ifdef ModoStreaming
	Serial.println("ModoStreaming");
#else
	Serial.println("ModoURL");
#endif
#endif
}

int Engine::freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

#ifdef ModoStreaming
int XinputChars = 0;
String _argS1 = "null";
String _argS2 = "null";
String _argS3 = "null";
String TextInput;
String Variavel;
char DELIM_1[] = "=";
char DELIM_2[] = "|";
char DELIM_3[] = ";";
char RESET[] = "R";
#endif

bool Engine::check() {
#ifdef ModoStreaming
#ifdef ModoEthernet
	EthernetClient _client = server.available();
#else
	WiFlyClient _client = server.available();
#endif
	if (_client.connected()) {
		while (_client.connected()) {
			while (_client.available()) {
				// if packet, reset loopCount
				//        loopCount = 0;
				char inputKey = _client.read();
				String CharStr = "";
				CharStr += inputKey;

				if (CharStr == "R") {
					//RESETA O ARDUINO APENAS COM UMA LETRA
#ifdef ServerDEBUG
					Serial.println("Reset actived");
#endif
#ifdef ModoEthernet
					_client.write("Resetado!");
#else
					const char *_output = "Resetado!";
					_client.write((uint8_t *)_output, strlen(_output));
					_client.write((uint8_t *) "\n", strlen(_output));
#endif
					delay(50);
					asm volatile("jmp 0");
					break;
				} else if (CharStr == "I") {
					//REALIZA UMA CONSULTA A URL, NO-IP ETC...
#ifdef ServerDEBUG
					Serial.println("Conectando URL");
#endif
					_customer->URLInitial(Client);
					delay(50);
					break;
				} else if (CharStr == "E") {
					const char *_output = Customer::_txtContainer.c_str();
					_client.write((uint8_t *) _output, strlen(_output));
					_client.write((uint8_t *) "\n", strlen(_output));
#ifdef ServerDEBUG
					Serial.println(_output);
#endif
					break;
				}
				else if (CharStr == DELIM_3) {
					//GET PARAM (ARGUMENTS)
					XinputChars++; //CONTA QUANTAS VARIÁVEIS ESTÃO DISPONÍVEIS
					if (XinputChars == 1) {
						_argS1 = TextInput;
					}
					else if (XinputChars == 2) {
						_argS2 = TextInput;
					}
					else if (XinputChars == 3) {
						_argS3 = TextInput;
					}
					TextInput = "";
				}
				else if (CharStr == DELIM_1) {
					//GET VARIÁVEL
					Variavel = TextInput;
					Variavel.trim();
					TextInput = "";
				}
				else if (CharStr == DELIM_2) {
					//EXEC FUNCTIONS
					XinputChars = 0;
#ifdef ServerDEBUG
					Serial.println("Class: " + Variavel + " -> (" + _argS1 + "," + _argS2 + "," + _argS3 + ")");
#endif
					return _customer->execStream(Variavel, _argS1, _argS2, _argS3);
				}
				else {
					TextInput += inputKey;
				}

			}
		}
	}
	return true;
#else
#ifdef ModoEthernet
	EthernetClient _client = server.available();
#else
	WiFlyClient _client = server.available();
#endif
	if (_client) {
		boolean currentLineIsBlank = true;
		boolean currentLineIsGet = true;
		int tCount = 0;
		char tBuf[65];
		int r, t;
		char *pch;
		char methodBuffer[8];
		char requestBuffer[48];
		char pageBuffer[48];
		char paramBuffer[48];
		char protocolBuffer[9];
		char fileName[32];
		char _method[4];
		char _temp[5];
		int clientCount = 0;
		String _class = "";

		requestNumber++;
#ifdef ServerDEBUG
		Serial.print(F("\r\nClient request #"));
		Serial.print(requestNumber);
		Serial.print(F(": "));
#endif

		// this controls the timeout
		int loopCount = 0;

		while (_client.connected()) {
			while (_client.available()) {
				// if packet, reset loopCount
				//        loopCount = 0;
				char c = _client.read();

				if (currentLineIsGet && tCount < 63)
				{
					tBuf[tCount] = c;
					tCount++;
					tBuf[tCount] = 0;
				}

				if (c == '\n' && currentLineIsBlank) {
#ifdef ServerDEBUG
					Serial.print(tBuf);
#endif
					//          Serial.print(F("POST data: "));
					while (_client.available()) _client.read();

					int scanCount = sscanf(tBuf, "%7s %47s %8s", methodBuffer, requestBuffer, protocolBuffer);

					if (scanCount != 3) {
#ifdef ServerDEBUG
						Serial.println(F("bad request #1"));
#endif
						return true;
					}

					char* pch = strtok(requestBuffer, "?");
					if (pch != NULL) {
						strncpy(fileName, pch, 31);
						strncpy(tBuf, pch, 31);

						pch = strtok(NULL, "?");
						if (pch != NULL) {
							strcpy(paramBuffer, pch);
						}
						else paramBuffer[0] = 0;
					}

					pch = strtok(tBuf, ".");
					int _pi = 0;
					while (pch != NULL)
					{
						if (_pi == 0) {
							strcpy(_temp, pch);
							int _pj = 0;

							for (char& c : _temp) {
								if (_pj > 0) {
									_class += c;
								}
								_pj++;
							}
						}
						else if (_pi == 1) {
							strcpy(_method, pch);
						}

						pch = strtok(NULL, ".");
						_pi++;
					}

#ifdef ServerDEBUG
					Serial.print(F("Class: "));
					Serial.println(_class);
					Serial.print(F("Method: "));
					Serial.println(_method);
					Serial.print(F("method = "));
					Serial.println(methodBuffer);
#endif
					if (strcmp(methodBuffer, "GET") != 0 && strcmp(methodBuffer, "HEAD") != 0) {
						Serial.print(F("sendBadRequest"));
						return true;
					}


					String _keys[5] = {};
					String _values[5] = {};

					char* command = strtok(paramBuffer, "&");
					int _pointer = 0;
					while (command != 0)
					{
						char* separator = strchr(command, '=');
						if (separator != 0)
						{
							*separator = 0;
							//Serial.println("S:" + (String)command);
							_keys[_pointer] = command;
							++separator;
							//Serial.println("V:" + (String)separator);
							_values[_pointer] = separator;
						}
						command = strtok(0, "&");
					}

					_customer->execURL(_class, _method, _keys, _values);

#ifdef ServerDEBUG
					Serial.print(F("params = "));
					Serial.println(paramBuffer);

					Serial.print(F("protocol = "));
					Serial.println(protocolBuffer);
					Serial.println(F("#Client"));
					// SRAM check
					Serial.print(F("SRAM = "));
					Serial.println(freeRam());
#endif

					strcpy_P(tBuf, PSTR("HTTP/1.0 200 OK\r\nContent-Type: "));
					strcat_P(tBuf, PSTR("text/json"));
					strcat_P(tBuf, PSTR("\r\nConnection: close\r\n\r\n"));

					if (strcmp(methodBuffer, "GET") == 0)
						strcpy_P(tBuf, PSTR("{""status"":""200"", ""method"":""method""}"));

					_client.write(tBuf);
					_client.stop();
#ifdef ServerDEBUG
					Serial.println(F("disconnected"));
#endif
					return true;
				}
				else if (c == '\n') {
					currentLineIsBlank = true;
					currentLineIsGet = false;
				}
				else if (c != '\r') {
					currentLineIsBlank = false;
				}
			}

			loopCount++;

			// if 1000ms has passed since last packet
			if (loopCount > 1000) {
				// close connection
				_client.stop();
#ifdef ServerDEBUG
				Serial.println("\r\nTimeout");
#endif
			}

			// delay 1ms for timeout timing
			delay(1);
		}
#ifdef ServerDEBUG
		Serial.println(F("disconnected"));
#endif
	}

	return true;
#endif
}

