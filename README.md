#Resumo:
Unificar um código de comunicação entre o arduino e computador. Atualmente, as principais interface de comunicação é a (1) USB, a (2) Ethernet e, similarmente a esta última, a de (3) Wireless.
O projeto usb-wifi-ethernet-arduino é único para todas as comunicações supracitadas, porém precisa ser configurado pelo arquivo Config.h de acordo com o método de comunicação utilizado.

O projeto arduino-software-communication trata a parte do software em VB.NET para desktop. O projeto usb-wifi-ethernet-arduino trata a programação do arduino.

![Alt text](/help/scheme.png?raw=true "Optional Title")

#Objetivo:

O usb-wifi-ethernet-arduino é um programa desenvolvido em C++ para ser implementado por qualquer usuário que utilize os tipos de arduino listados abaixo:

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

#Como personalizar minhas proprias ações no arduino?
As configurações são realizadas dentro do arquivo Customer.cpp.
O método init deve conter as configurações usualmente inseridas no Setup(). 

Exemplo: pinMode(13, OUTPUT); //PARA PISCAR O LED A PARTIR DE UMA INSTRUÇÃO DE UM COMPUTADOR

O método execStream é chamado sempre que uma ordem for dada ao arduino.
Seguindo a numeração dos caracteres em ASCII, temos:
A = 65, B = 66, C = 67, e assim por diante.

Obs.: A letra E é reservada para leitura do arduino pelo software desktop bem como a letra R reinicia o arduino. Portanto, essas não devem ser usadas.

Se quisermos que o led acoplado a porta 13 do arduino seja aceso ou apagado por comando de um software, devemos configurar da seguinte forma:
Quando eu enviar A ele irá ligar, quando enviar B ele irá apagar.
```c
bool Customer::execStream(int _class, char _p[]) {
	if (_class == 65) {

		/* AÇÃO NO ARDUINO */

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


