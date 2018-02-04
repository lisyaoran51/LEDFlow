#include "StatusConverter.h"

StatusConverter::StatusConverter(int wLights, int wDest, int bLights, int bDest) {
	whiteLights = wLights;
	whiteDest = wDest;
	blackLights = bLights;
	blackDest = bDest;
#ifdef DEBUG_MODE
  debugbool = false;
#endif
  
}

void StatusConverter::Convert(LinkedList<Event*>* events, LinkedList<Pair>* lStatus)
{
  lStatus -> clear();
  
#ifdef _DEBUG_MODE
    if(debugbool) DEBUG_PRINT("events have ");
    if(debugbool) DEBUG_PRINTLN(events->size());
#endif
  
	for (int i = 0; i < events->size(); i++) {
    // TODO: should determine which event this is
		NoteEvent* e = (NoteEvent*)events->get(i);

		int pitch = e->GetPitch();
		int led = ComputeLED(pitch, e->GetTimeLeft(), e->GetTotalTime());
#ifdef DEBUG_MODE
    String d1 = String("LED # is") + led + ", time left is " + e->GetTimeLeft() + ", total time is " + e->GetTotalTime();
    DEBUG_PRINTLN(d1);
#endif
		if (led == -1) 
			continue;
     
    Pair p;
    p.first = pitch;
    p.second = led;
		lStatus->add(p);
   
    
#ifdef DEBUG_MODE
    if(debugbool) DEBUG_PRINT("lStatus have ");
    if(debugbool) DEBUG_PRINTLN(lStatus->size());
    debugbool = true;
    DEBUG_PRINT("Convert event to status:");
    DEBUG_PRINT(pitch);
    DEBUG_PRINT(" ");
    DEBUG_PRINTLN(led);
#endif
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



