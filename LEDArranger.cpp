#include "LEDArranger.h"

LEDArranger::LEDArranger(StatusConverter* sConverter) {
	startTime = clock();
	converter = sConverter;
}

void LEDArranger::AddEvents(LinkedList<Event*>* newEvents)
{
	for (int i = 0; i < newEvents->size(); i++) {
		events.add(newEvents->get(i));
	}
	free(newEvents);
}

void LEDArranger::Update() 
{
	long nowTime = clock();
	long deltaTime = now - lastTime;
	/*
	 * pass every event update time, kill dead ones
	 */
	for (int i = 0; i < events.size(); i++)
	{
		Event* e = events.get(i);
		e->PassBy(deltaTime);
		
		if (!e->IsAlive()) {
			events.remove(i);
			free(e);
			i--;
		}
	}
}

void LEDArranger::Arrange(LinkedList<Pair>* lightStatus)
{
	converter.Convert(&events, lightStatus);
}