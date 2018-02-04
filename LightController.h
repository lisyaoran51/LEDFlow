#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <string.h>
#include <LinkedList.h> 
#include "Pair.h"
#include "ShiftRegisterController.h"
#include "PitchToKeyboardConverter.h"
#include "Debug.h"


class LightController
{
public:
	LightController(ShiftRegisterController* sReg, PitchToKeyboardConverter* cnvr);
	void Run();
	void Update(LinkedList<Pair>* lStatus);

private:
	LinkedList<Pair>* lightStatus;
	LinkedList<Pair>* ledStatus;
	ShiftRegisterController* shiftReg;
	PitchToKeyboardConverter* converter;

	bool compare(LinkedList<Pair>* lStatus);
	void update(LinkedList<Pair>* lStatus);
};

#endif //LIGHT_CONTROLLER_H


