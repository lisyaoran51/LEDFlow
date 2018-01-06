#ifndef EVENT_H
#define EVENT_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#define NOTE_DEAD_TIME 1.0


class Event {
public:
	Event();
	void virtual PassBy(float deltaTime);
	bool virtual IsAlive();

protected:
	float totalTime;
};



class NoteEvent: public Event
{
public:
	NoteEvent(int p, float tLeft);
private:
	int pitch;
	float timeLeft;
	float deadTime;
};




#endif //EVENT_H