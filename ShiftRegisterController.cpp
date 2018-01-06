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
		byteBuilders[i].Set(rowReg, colReg);
	}

	Pair p = Pair(0, 0);
	for (int i = 0; i < lStatus->size(); i++)
	{
		p = lStatus->get(i);

		/*
		 * put the key(p.first) into the builder which contains the specific led light row(p.second)
		 */
		byteBuilders[p.second].Add(p.first);
	}

	for (int i = 0; i < row; i++) {
		free(bytes[i]);
		bytes[i] = byteBuilders[i].Build();
	}
}

void ShiftRegisterController::Run() {
	// turn off led
	digitalWrite(latchPin, LOW);

	// change data
	for (int i = 0; i < bytes.size(); i++) {
		shiftOut(dataPin, clockPin, MSBFIRST, bytes.get(i));
	}

	// turn on led
	digitalWrite(latchPin, HIGH);
}

void ShiftRegisterController::clear() {
	ledStatus.clear();

	for (int i = 0; i < bytes.size(); i++) {
		free(bytes.get(i));
	}
	bytes.clear();
}