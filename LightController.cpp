#include "LightController.h"

LightController::LightController(ShiftRegisterController* sReg, PitchToKeyboardConverter* cnvr) {
	shiftReg = sReg;
	converter = cnvr;
	lightStatus = new LightStatus();
}

void LightController::Light() {
	shiftReg->ShiftOut();
}

void LightController::Update(LinkedList<Pair>* lStatus) {
	
	if (lightStatus->Compare(lStatus)) return;

	ledStatus.clear();
	converter->Convert(lStatus, &ledStatus);
	shiftReg->Set(&ledStatus);
}