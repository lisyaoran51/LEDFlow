#ifndef EVENT_H
#define EVENT_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#define NOTE_DEAD_TIME -1.0


class Event {
public:
	Event();
	virtual void PassBy(float deltaTime);
	virtual bool IsAlive();

protected:
	float totalTime;
};



class NoteEvent: public Event
{
public:
	NoteEvent(int p, float tLeft);

  void PassBy(float deltaTime);
  bool IsAlive();
  int GetPitch();
  float GetTimeLeft();
  float GetTotalTime();
private:
	int pitch;
	float timeLeft;
	float deadTime;
};




#endif //EVENT_H


