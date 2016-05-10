#Resumo:
Unificar um código de comunicação entre o arduino e o computador. Atualmente, as principais interface de comunicação é a (1) USB, a (2) Ethernet e, similarmente a esta última, a de (3) Wireless.
O projeto usb-wifi-ethernet-arduino é único para todas as comunicações supracitadas, porém precisa ser configurado pelo arquivo Config.h de acordo com o método de comunicação utilizado.

O projeto arduino-software-communication trata a parte do software em VB.NET para desktop. Por outro lado, o projeto [usb-wifi-ethernet-arduino](https://github.com/labqui/usb-wifi-ethernet-arduino) a programação do arduino.

![Alt text](/help/scheme.png?raw=true "Optional Title")

#Objetivo:

O usb-wifi-ethernet-arduino é um programa desenvolvido em C++ para ser implementado por qualquer usuário que utilize os tipos de arduino listados abaixo:

| Tipo de Arduino | Código no Projeto |
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

Feito isso, a programação do arduino para a comunicação está funcionando.

#Como personalizar minhas proprias ações no arduino?
As configurações são realizadas dentro do arquivo Customer.cpp.
O método init deve conter as configurações usualmente inseridas no ```Setup()```. 

Exemplo: ```c pinMode(13, OUTPUT); //PARA PISCAR O LED A PARTIR DE UMA INSTRUÇÃO DE UM COMPUTADOR ```

O método ```execStream``` é chamado sempre que uma ordem for dada ao arduino.


Seguindo a numeração dos caracteres em ASCII ([lista completa](help/asciifull.gif), temos:

A = 65, B = 66, C = 67, e assim por diante. Cada letra representa um método que no arduino.

Obs.: A letra E é reservada para leitura do arduino pelo software desktop bem como a letra R reinicia o arduino. Portanto, essas não devem ser usadas.

Se quisermos que o led, acoplado a porta 13 de alguns arduinos, seja aceso ou apagado por comando de um software, devemos configurar esta aplicação da seguinte forma:

Quando enviar o comando ```c A=1; ``` a função entrará na condição ```c if (_class == 65) ``` e passará ```c 100 ``` como parâmetro. Por outro lado, quando enviarmos ```c A=0; ``` ele irá apagar o led.
```c
bool Customer::execStream(int _class, char _p[]) {
	if (_class == 65) {
		digitalWrite(13, atoi(_p)); //liga o led do arduino
		BaseDuino::_txtContainer = "LED:ON";
	}
	else if (_class == 66) {
		//UMA AÇÃO PARA A LETRA B
	}
	return true;
}
```


