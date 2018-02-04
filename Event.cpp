#include "Event.h"

Event::Event(){}
void Event::PassBy(float deltaTime) {}
bool Event::IsAlive() { return false; }



NoteEvent::NoteEvent(int p, float tLeft):Event() {
	pitch = p;
	totalTime = tLeft;
	timeLeft = tLeft;
	deadTime = NOTE_DEAD_TIME;
}

void NoteEvent::PassBy(float deltaTime) {
	timeLeft -= deltaTime;
}

bool NoteEvent::IsAlive() {
	return timeLeft > deadTime;
}

int NoteEvent::GetPitch(){
  return pitch;
}

float NoteEvent::GetTimeLeft(){
  return timeLeft;
}

float NoteEvent::GetTotalTime(){
  return totalTime;
}



