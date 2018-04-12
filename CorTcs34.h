#ifndef COR_TCS34_H
#define COR_TCS34_H

#include <Arduino.h>
#include "Adafruit_TCS34725.h"
#include "CorHardware.h"

class CorTcs34{
	private:
	static Adafruit_TCS34725 tcsCorHardware;

	public:
	CorTcs34(int pinLigaDesliga);

};

#endif