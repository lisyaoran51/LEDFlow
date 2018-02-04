#ifndef STATUS_CONVERTER_H
#define STATUS_CONVERTER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <string.h>
#include <LinkedList.h> 
#include "time.h" 
#include "Event.h" 
#include "Pair.h"
#include <LinkedList.h> 
#include "Debug.h"


class StatusConverter
{
public:
	StatusConverter(int wLights, int wDest, int bLights, int bDest);
	void Convert(LinkedList<Event*>* events, LinkedList<Pair>* lStatus);

#ifdef DEBUG_MODE
  bool debugbool;
#endif

private:
	int whiteLights;		// how many light to tail of key
	int whiteDest;			// how many light to hit point
	int blackLights; 
	int blackDest; 

	int ComputeLED(int pitch, float timeLeft, float totalTime);
  bool isWhite(int pitch);
};

#endif //LED_ARRANGER_H


