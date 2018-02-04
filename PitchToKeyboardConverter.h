#ifndef PITCH_TO_KEYBOARD_CONVERTER_H
#define PITCH_TO_KEYBOARD_CONVERTER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <string.h>
#include <LinkedList.h> 
#include "Pair.h"


class PitchToKeyboardConverter
{
public:
	PitchToKeyboardConverter(int minP, int maxP);
	void Convert(LinkedList<Pair>* lightS, LinkedList<Pair>* ledS);

private:
	int minPitch;
	int maxPitch;
};

#endif //PITCH_TO_KEYBOARD_CONVERTER_H


