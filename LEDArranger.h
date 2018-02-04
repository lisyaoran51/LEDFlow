#ifndef LED_ARRANGER_H
#define LED_ARRANGER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Debug.h"
#include <string.h>
#include <LinkedList.h> 
#include "Event.h" 
#include "StatusConverter.h"
#include "Pair.h"


class LEDArranger
{
public:
	LEDArranger(StatusConverter* sConverter);
	void AddEvents(LinkedList<Event*>* newEvents);
	void Update();
	void Arrange(LinkedList<Pair>* lightStatus);

private:
	LinkedList<Event*> events;
	float startTime, lastTime;
	StatusConverter* converter;

};

#endif //LED_ARRANGER_H


