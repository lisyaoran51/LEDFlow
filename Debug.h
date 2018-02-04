#ifndef DEBUG_H
#define DEBUG_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define DEBUG_MODE

#ifdef DEBUG_MODE
	#define DEBUG_PRINTLN(x) Serial.println(x)
	#define DEBUG_PRINT(x) Serial.print(x)
#else
	#define DEBUG_PRINTLN(x)
    #define DEBUG_PRINT(x)
#endif

#endif


