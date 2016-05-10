#Resumo:
Unificar um c�digo de comunica��o entre o arduino e o computador. Atualmente, as principais interface de comunica��o � a (1) USB, a (2) Ethernet e, similarmente a esta �ltima, a de (3) Wireless.
O projeto usb-wifi-ethernet-arduino � �nico para todas as comunica��es supracitadas, por�m precisa ser configurado pelo arquivo Config.h de acordo com o m�todo de comunica��o utilizado.

O projeto arduino-software-communication trata a parte do software em VB.NET para desktop. Por outro lado, o projeto [usb-wifi-ethernet-arduino](https://github.com/labqui/usb-wifi-ethernet-arduino) a programa��o do arduino.

![Alt text](/help/scheme.png?raw=true "Optional Title")

#Objetivo:

O usb-wifi-ethernet-arduino � um programa desenvolvido em C++ para ser implementado por qualquer usu�rio que utilize os tipos de arduino listados abaixo:

| Tipo de Arduino | C�digo no Projeto |
| Arduino qualquer com interface USB | 1 |
| ------------- |:-------------:|
| Arduino Ethernet      | 2 |
| Arduino com o shield Wireless [sparkfun/WiFly-Shield](https://github.com/sparkfun/WiFly-Shield)      | 3 |


#Como configurar?

a) Arquivo Config.h

```c
#define TypeArduino 1 // Use 1 para USB, 2 para Ethernet ou 3 para WiFly
```

b) Arquivo Kernel.ino
Altere a classe UsbDuino para UsbDuino, EtheDuino ou WifliDuino de acordo com o escolhido pelo item anterior.

```c
UsbDuino *_b; //Altere para UsbDuino, EtheDuino ou WifliDuino

void setup() {
	SERIAL_DEBUG_SETUP(9600);
	DEBUG("Available memory", FREE_RAM);
	_b = new UsbDuino(); //Altere para UsbDuino, EtheDuino ou WifliDuino
	_b->init();
	//_b->addSSID("SSID", "PASS"); //ONLY TO CLASS WifiDuino
	_b->Connect();
}

void loop() {
	_b->loop();
}
```

Feito isso, a programa��o do arduino para a comunica��o est� funcionando.

#Como personalizar minhas proprias a��es no arduino?
As configura��es s�o realizadas dentro do arquivo Customer.cpp.
O m�todo init deve conter as configura��es usualmente inseridas no ```Setup()```. 

Exemplo: ```c pinMode(13, OUTPUT); //PARA PISCAR O LED A PARTIR DE UMA INSTRU��O DE UM COMPUTADOR ```

O m�todo ```execStream``` � chamado sempre que uma ordem for dada ao arduino.


Seguindo a numera��o dos caracteres em ASCII ([lista completa](help/asciifull.gif), temos:

A = 65, B = 66, C = 67, e assim por diante. Cada letra representa um m�todo que no arduino.

Obs.: A letra E � reservada para leitura do arduino pelo software desktop bem como a letra R reinicia o arduino. Portanto, essas n�o devem ser usadas.

Se quisermos que o led, acoplado a porta 13 de alguns arduinos, seja aceso ou apagado por comando de um software, devemos configurar esta aplica��o da seguinte forma:

Quando enviar o comando ```c A=1; ``` a fun��o entrar� na condi��o ```c if (_class == 65) ``` e passar� ```c 100 ``` como par�metro. Por outro lado, quando enviarmos ```c A=0; ``` ele ir� apagar o led.
```c
bool Customer::execStream(int _class, char _p[]) {
	if (_class == 65) {
		digitalWrite(13, atoi(_p)); //liga o led do arduino
		BaseDuino::_txtContainer = "LED:ON";
	}
	else if (_class == 66) {
		//UMA A��O PARA A LETRA B
	}
	return true;
}
```


