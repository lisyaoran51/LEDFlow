#include "Event.h"

void virtual Event::PassBy(float deltaTime) {}
bool virtual Event::IsAlive() { return false; }



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
	return timeLeft < deadTime;
}
