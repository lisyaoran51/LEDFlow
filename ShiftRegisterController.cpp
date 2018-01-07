#include "ShiftRegisterController.h"


ShiftRegisterController::ShiftRegisterController(int latch, int clock, int data, int keyAmount, int ledLength) {
	latchPin = latch;
	clockPin = clock;
	dataPin = data;
	col = keyAmount;
	row = ledLength;

	rowReg = row / 8 + (row % 8 > 0 ? 1 : 0);
	colReg = col / 8 + (col % 8 > 0 ? 1 : 0);
	totalReg = rowReg + colReg;

	bytes = new byte*[row];
	for (int i = 0; i < row; i++) {
		bytes[i] = new byte[totalReg];
		for (int j = 0; j < totalReg; j++) {
			bytes[i][j] = 0b00000000;
		}
	}

	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);

}


void ShiftRegisterController::Set(LinkedList<Pair>* lStatus) {


	ByteBuilder byteBuilders[row];
	for (int i = 0; i < row; i++) {
		byteBuilders[i].Set(i, rowReg, colReg);
	}

	Pair p;
	for (int i = 0; i < lStatus->size(); i++)
	{
		p = lStatus->get(i);

		/*
		 * put the key(p.first) into the builder which contains the specific led light row(p.second)
		 */
		byteBuilders[p.second].Add(p.first);
	}

	for (int i = 0; i < row; i++) {
		delete [] bytes[i];
		bytes[i] = byteBuilders[i].Build();
	}
}

void ShiftRegisterController::Run() 
{
	for (int i = 0; i < row; i++) {
		// turn off led
		digitalWrite(latchPin, LOW);

		// change data
		for (int j = 0; j < totalReg; j++) {
			shiftOut(dataPin, clockPin, MSBFIRST, bytes[i][j]);
		}

		// turn on led
		digitalWrite(latchPin, HIGH);

		// stay lightened for a while
		// delay(40);
	}
	
}

void ShiftRegisterController::clear() {

	for (int i = 0; i < totalReg; i++) {
		delete [] bytes[i];
	}
	delete [] bytes;
}
