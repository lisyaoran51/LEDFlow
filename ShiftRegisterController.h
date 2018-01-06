#ifndef SHIFT_REGISTER_CONTROLLER_H
#define SHIFT_REGISTER_CONTROLLER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <string.h>
#include <LinkedList.h> 
#include "LightStatus.h"
#include "Pair.h"
#include "ByteConverter.h"

class ShiftRegisterController
{
public:
	ShiftRegisterController(int latch, int clock, int data, int kAmount, int lLength);
	void Set(LedStatus* lStatus);
	void Run();

private:
	int latchPin;
	int clockPin;
	int dataPin;
	int keyAmount;
	int ledLength;

	LinkedList<Pair> ledStatus;
	LinkedList<uint8_t*> bytes;
	
	static ByteConverter byteConverter;

	void clear();
};

#endif //SHIFT_REGISTER_CONTROLLER_H