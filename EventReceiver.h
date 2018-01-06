#ifndef EVENT_RECEIVER_H
#define EVENT_RECEIVER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <string.h>
#include <LinkedList.h>
#include <SoftwareSerial.h>
#include <SerialCommand.h>
#include <stdlib.h>     /* atof */
#include "Event.h"


class EventReceiver
{
public:
	EventReceiver();

	void PassBy();
	LinkedList<Event*>* Pop();

private:
	LinkedList<Event*> events;
	SerialCommand sCmds;
	void receive();
};

#endif //EVENT_RECEIVER_H