#Resumo:
Unificar um c�digo de comunica��o entre o arduino e computador. Atualmente, as principais interface de comunica��o � a (1) USB, a (2) Ethernet e, similarmente a esta �ltima, a de (3) Wireless.
O projeto usb-wifi-ethernet-arduino � �nico para todas as comunica��es supracitadas, por�m precisa ser configurado pelo arquivo Config.h de acordo com o m�todo de comunica��o utilizado.

O projeto arduino-software-communication trata a parte do software em VB.NET para desktop. O projeto usb-wifi-ethernet-arduino trata a programa��o do arduino.

![Alt text](/help/scheme.png?raw=true "Optional Title")

#Objetivo:

O usb-wifi-ethernet-arduino � um programa desenvolvido em C++ para ser implementado por qualquer usu�rio que utilize os tipos de arduino listados abaixo:

- Arduino Ethernet
- Arduino com o shield da #WiFly-Shield de Wireless
- Arduino qualquer com interface USB

#Como configurar?

a) Arquivo Config.h

```c
#define TypeArduino 1 // Use 1 para USB, 2 para Ethernet ou 3 para WiFly
```

b) Arquivo Kernel.ino
Altere a classe UsbDuino para UsbDuino, EtheDuino ou WifliDuino de acordo com o escolhido pelo item anterior.

#Como personalizar minhas proprias a��es no arduino?
As configura��es s�o realizadas dentro do arquivo Customer.cpp.
O m�todo init deve conter as configura��es usualmente inseridas no Setup(). 

Exemplo: pinMode(13, OUTPUT); //PARA PISCAR O LED A PARTIR DE UMA INSTRU��O DE UM COMPUTADOR

O m�todo execStream � chamado sempre que uma ordem for dada ao arduino.
Seguindo a numera��o dos caracteres em ASCII, temos:
A = 65, B = 66, C = 67, e assim por diante.

Obs.: A letra E � reservada para leitura do arduino pelo software desktop bem como a letra R reinicia o arduino. Portanto, essas n�o devem ser usadas.

Se quisermos que o led acoplado a porta 13 do arduino seja aceso ou apagado por comando de um software, devemos configurar da seguinte forma:
Quando eu enviar A ele ir� ligar, quando enviar B ele ir� apagar.
```c
bool Customer::execStream(int _class, char _p[]) {
	if (_class == 65) {

		/* A��O NO ARDUINO */

		digitalWrite(13, HIGH); //liga led da placa UNO

		BaseDuino::_txtContainer = "LED:ON";
	}
	else if (_class == 66) {
		digitalWrite(13, LOW); //liga led da placa UNO
		BaseDuino::_txtContainer = "LED:OFF";
	}
	return true;
}
```


