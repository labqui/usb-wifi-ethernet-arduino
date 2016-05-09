#include "BaseDuino.h"

char _text[20];
char func;

String BaseDuino::_txtContainer = "";

BaseDuino::BaseDuino() {
	Customer::init();
};

void BaseDuino::parse(char inputKey) {
	switch (inputKey) {
	case 61: //=
		func = oinputKey;
		DEBUG("Call", func);
		_count = 0;
		break;
	case 59: //;
		for (int i = _count; i <= 20; i++) {
			_text[i] = 0;
		}
		DEBUG("@param", _text);
		Customer::execStream(func, _text);
		return;
		break;
	default:
		_text[_count] = inputKey;
		_count++;
	}
	oinputKey = inputKey;
}


void BaseDuino::write(String _w) {
	_txtContainer = _w;
};

