#include "LEDArranger.h"

LEDArranger::LEDArranger(StatusConverter* sConverter) {
	startTime = float(millis()) / 1000.0;
  lastTime = startTime;
	converter = sConverter;
}

void LEDArranger::AddEvents(LinkedList<Event*>* newEvents)
{
  
	for (int i = 0; i < newEvents->size(); i++) {
		events.add(newEvents->get(i));
	}

	delete newEvents;
}

void LEDArranger::Update() 
{
	float nowTime = float(millis()) / 1000.0;
	float deltaTime = nowTime - lastTime;
#ifdef _DEBUG_MODE
  String d2 = String("Now time: ") + millis() + "really get time: " + String(float(nowTime),3);
  DEBUG_PRINTLN(d2);
#endif
	/*
	 * pass every event update time, kill dead ones
	 */
	for (int i = 0; i < events.size(); i++)
	{
		Event* e = events.get(i);
		e->PassBy(deltaTime);
		
		if (!e->IsAlive()) {
#ifdef DEBUG_MODE
      NoteEvent* debugE = (NoteEvent*)e;
      String d = String("Kill dead event. Now time: ") + nowTime + ", Last time: " + lastTime + ", time left: " + debugE->GetTimeLeft() + ", dead time: " + NOTE_DEAD_TIME;
      DEBUG_PRINTLN(d);
#endif
			events.remove(i);
			delete e;
			i--;
		}
	}
  lastTime = nowTime;
}

void LEDArranger::Arrange(LinkedList<Pair>* lightStatus)
{
	converter->Convert(&events, lightStatus);
}


