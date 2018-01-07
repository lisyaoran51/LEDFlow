#include <LinkedList.h>
#include <StaticThreadController.h>
#include <Thread.h>
#include <ThreadController.h>
#include "EventReceiver.h"
#include "StatusConverter.h"
#include "LEDArranger.h"
#include "LightController.h"
#include "ShiftRegisterController.h"
#include "PitchToKeyboardConverter.h"

EventReceiver eventReceiver;
StatusConverter statusConverter = StatusConverter(11, 10, 7, 6);                              // whiteLength, whiteDestination, blackLength, blackDestination
LEDArranger lEDArranger = LEDArranger(&statusConverter);
LinkedList<Pair> lightStatus;
ShiftRegisterController shiftRegisterController = ShiftRegisterController(8, 12, 11, 36, 11); // latch, clock, data, keyAmount, ledLength
PitchToKeyboardConverter pitchToKeyboardConverter = PitchToKeyboardConverter(48, 72);         // minPitch, maxPitch
LightController lightController = LightController(&shiftRegisterController, &pitchToKeyboardConverter);

ThreadController threadController;
Thread updateThread;
Thread runThread;

void updateCallback(){
  //thread1
  eventReceiver.Receive();
  lEDArranger.AddEvents(eventReceiver.Pop());
  lEDArranger.Update();
  
  lEDArranger.Arrange(&lightStatus);

  lightController.Update(&lightStatus);
}

void runCallback(){
   //thread2
  lightController.Run();
}


void setup() {
  Serial.begin(9600);

  updateThread.onRun(updateCallback);
  updateThread.setInterval(100);
  runThread.onRun(runCallback);
  runThread.setInterval(0);

  threadController.add(&updateThread);
  threadController.add(&runThread);
}


void loop() {
  threadController.run();
}
