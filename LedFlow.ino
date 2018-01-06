#include <LinkedList.h>



void setup() {
  // put your setup code here, to run once:

}

int* gg(){
  int i = 1;
  return &i;
}

void loop() {
  //thread1
  eventReceiver.Receive();
  lEDArranger.AddEvents(eventReceiver.Pop());
  lEDArranger.Update();
  
  LightStatus* memToFree = &lightStatus;
  &lightStatus = lEDArranger.Arrange();
  free(memToFree);
  
  //thread2
  lightController.Control(&lightStatus);
  
}
