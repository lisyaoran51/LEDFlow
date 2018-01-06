#include "EventReceiver.h"



EventReceiver::EventReceiver() 
{
	events = new LinkedList<Event*>();
	//sCmds = SerialCommand();
	sCmds.addCommand("Event", receive);
}

void EventReceiver::receive() {
	if (events.size() != 0) {
		//Serial.println("Error: EventReceiver::Receive() failed to receive because events is not empty.");
		//pinMode(13, OUTPUT);
		//while (1) {
		//	digitalWrite(13, HIGH);  // to warn user by blinking lights
		//	delay(100);
		//	digitalWrite(13, LOW);
		//	delay(100);
		//}
	}
	char *arg;
	arg = sCmds.next();    // Get the next argument from the SerialCommand object buffer
	Event* e = NULL;
	if (arg != NULL)      // As long as it existed, take it
	{

		switch (arg) {
		case "Note":
			arg = sCmds.next();
			if (arg == NULL) break;
			int pitch = atoi(arg);
			arg = sCmds.next();
			if (arg == NULL) break;
			float timeLeft = atof(arg);
			e = new NoteEvent(pitch, timeLeft);
			events.add(e);
			break;
		}
	}
}

void EventReceiver::Receive() {
	sCmds.readSerial();
}

LinkedList<Event*>* EventReceiver::Pop() 
{
	LinkedList<Event*>* listToPop = events;
	events = new LinkedList<Event*>();
	return listToPop;
}