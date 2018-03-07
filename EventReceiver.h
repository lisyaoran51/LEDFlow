#ifndef EVENT_RECEIVER_H
#define EVENT_RECEIVER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Debug.h"
#include <string.h>
#include <LinkedList.h>
#include <SoftwareSerial.h>
#include "MySerialCommand.h"
#include <stdlib.h>     /* atof */
#include "Event.h"


static LinkedList<Event*> bufEvents;
static SerialCommand* sCommand;


class EventReceiver
{
public:
	EventReceiver();

  void Receive();
  
  static void ReadSerial();
	void PassBy();
	LinkedList<Event*>* Pop();
  int Size();
  
  
private:
	LinkedList<Event*>* events;
	SerialCommand sCmds;

  void getEvent();
};

#endif //EVENT_RECEIVER_H


