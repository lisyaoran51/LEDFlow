#include "PitchToKeyboardConverter.h"


PitchToKeyboardConverter::PitchToKeyboardConverter(int minP, int maxP) {
	minPitch = minP;
	maxPitch = maxP;
}

void PitchToKeyboardConverter::Convert(LightStatus* lightS, LinkedList<LEDStatus>* ledS) {
	for (int i = 0; i < lightS->size(); i++) {
		Pair p = lightS->get(i);
		ledS->add(Pair(p.first - minPitch, p.second));
	}
}