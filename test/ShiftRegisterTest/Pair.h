#ifndef PAIR_H
#define PAIR_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

struct Pair {
	int first;
	int second;
};

#endif //PAIR_H


