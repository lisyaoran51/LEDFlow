#include "EventReceiver.h"



EventReceiver::EventReceiver() 
{
  events = new LinkedList<Event*>();
  sCommand = &sCmds;
  sCmds.addCommand("Event", ReadSerial);
}

void EventReceiver::getEvent() {
  for(int i = 0; i < bufEvents.size(); i++){
    events->add(bufEvents.get(i));
    DEBUG_PRINTLN("Event Receiver Got Event");
	}
  bufEvents.clear();
}

void EventReceiver::Receive() {
	sCmds.readSerial();
  getEvent();
}

LinkedList<Event*>* EventReceiver::Pop() 
{
	LinkedList<Event*>* listToPop = events;
	events = new LinkedList<Event*>();
	return listToPop;
}

int EventReceiver::Size(){
  return events->size();
}

static void EventReceiver::ReadSerial(){
  char *arg;
  Event* e;
  arg = sCommand->next();    // Get the next argument from the SerialCommand object buffer
  if (arg != NULL)      // As long as it existed, take it
  {
    if(strcmp(arg, "Note") == 0){
      DEBUG_PRINT(arg);
      arg = sCommand->next();
      if (arg == NULL) return;
      int pitch = atoi(arg);
      DEBUG_PRINT(arg);
      arg = sCommand->next();
      if (arg == NULL) return;
      float timeLeft = atof(arg);
      DEBUG_PRINTLN(arg);
      e = new NoteEvent(pitch, timeLeft);
      bufEvents.add(e);
    }
  }
}



