#include "ShiftRegisterController.h"


ShiftRegisterController::ShiftRegisterController(int latch, int clock, int data, int kAmount, int lLength) {
	latchPin = latch;
	clockPin = clock;
	dataPin = data;
	keyAmount = kAmount;
	ledLength = lLength;

	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);

}


void ShiftRegisterController::Set(LedStatus* lStatus) {

	Pair p = Pair(0, 0);

	clear();

	for (Iterator* i = lStatus->GetIterator(); i->HasNext(); i->Next()) 
	{
		p = i->Get();
		ledStatus->Add(p);
		
		// convert to bytes
		byteConverter.Convert(
			&bytes,
			ledLength % 8 > 0 ? ledLength / 8 + 1 : ledLength / 8, // get y dimension 595 amounts by key length
			p.First);

		byteConverter.Convert(
			&bytes,
			keyAmount % 8 > 0 ? keyAmount / 8 + 1 : keyAmount / 8, // get dimension of 74hc595 amounts by key amounts
			p.Second);

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