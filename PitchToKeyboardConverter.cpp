#include "PitchToKeyboardConverter.h"


PitchToKeyboardConverter::PitchToKeyboardConverter(int minP, int maxP) {
	minPitch = minP;
	maxPitch = maxP;
}

void PitchToKeyboardConverter::Convert(LinkedList<Pair>* lightS, LinkedList<Pair>* ledS) {
	for (int i = 0; i < lightS->size(); i++) {
    Pair p = lightS->get(i);
    p.first = p.first - minPitch;
		ledS->add(p);
	}
}
