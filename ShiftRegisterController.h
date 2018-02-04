#ifndef SHIFT_REGISTER_CONTROLLER_H
#define SHIFT_REGISTER_CONTROLLER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <string.h>
#include <LinkedList.h> 
#include "Pair.h"
#include "ByteBuilder.h"


class ShiftRegisterController
{
public:
	ShiftRegisterController(int latch, int clock, int data, int kAmount, int lLength);
	void Set(LinkedList<Pair>* lStatus);
	void Run();

private:
	int latchPin;
	int clockPin;
	int dataPin;
	int row;
	int col;
	int rowReg;
	int colReg;
	int totalReg;

	byte** bytes;
	
	static ByteBuilder bytebuilder;

	void clear();
};

#endif //SHIFT_REGISTER_CONTROLLER_H


