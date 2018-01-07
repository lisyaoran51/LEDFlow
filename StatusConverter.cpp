#include "StatusConverter.h"

StatusConverter::StatusConverter(int wLights, int wDest, int bLights, int bDest) {
	whiteLights = wLights;
	whiteDest = wDest;
	blackLights = bLights;
	blackDest = bDest;
}

void StatusConverter::Convert(LinkedList<Event*>* events, LinkedList<Pair>* lStatus)
{
	for (int i = 0; i < events->size(); i++) {
		NoteEvent* e = (NoteEvent*)events->get(i);

		int pitch = e->GetPitch();
		int led = ComputeLED(pitch, e->GetTimeLeft(), e->GetTotalTime());

		if (led == -1) 
			return;
     
    Pair p;
    p.first = pitch;
    p.second = led;
		lStatus->add(p);
	}
}

int StatusConverter::ComputeLED(int pitch, float timeLeft, float totalTime) {
	float dest = isWhite(pitch) ? whiteDest : blackDest;
	/*
	 *   | o | o | o | o | o |     lights
	 *  0.5 1.5 2.5 3.5 4.5 5.5    time pass
	 * 
	 */
	float lightPlace = (totalTime - timeLeft) / totalTime * dest - 0.5f;

	int lights = isWhite(pitch) ? whiteLights : blackLights;
	if ((int)lightPlace >= lights) 
		return -1;

	return (int)lightPlace > 0 ? (int)lightPlace : 0;
}

bool StatusConverter::isWhite(int pitch){
  int k = pitch % 12;
  if( k == 0 || 
      k == 2 ||
      k == 4 ||
      k == 5 ||
      k == 7 ||
      k == 9 ||
      k == 11 )
      return true;
  else
      return false;
}

