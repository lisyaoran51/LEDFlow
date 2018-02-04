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
#include "Debug.h"

EventReceiver eventReceiver;
StatusConverter statusConverter = StatusConverter(11, 10, 7, 6);                              // whiteLength, whiteDestination, blackLength, blackDestination
LEDArranger lEDArranger = LEDArranger(&statusConverter);
LinkedList<Pair> lightStatus;
ShiftRegisterController shiftRegisterController = ShiftRegisterController(8, 12, 11, 36, 11); // latch, clock, data, keyAmount, ledLength
PitchToKeyboardConverter pitchToKeyboardConverter = PitchToKeyboardConverter(52, 83);         // minPitch, maxPitch
LightController lightController = LightController(&shiftRegisterController, &pitchToKeyboardConverter);

ThreadController threadController;
Thread updateThread;
Thread runThread;
//int debugb = 0;

void updateCallback(){
  //thread1
    //if(debugb==1) debugb++;                                       //
    eventReceiver.Receive();
    //if(eventReceiver.Size()>0 && debugb == 0) debugb = 1;         //

    //DEBUG_PRINT("This thread debug:");
    //DEBUG_PRINTLN(debugb);                                       //
    
    lEDArranger.AddEvents(eventReceiver.Pop());
    lEDArranger.Update();
    lEDArranger.Arrange(&lightStatus);
    //if(debugb == 2) delay(10000);                                 //
    lightController.Update(&lightStatus);
#ifdef _DEBUG_MODE
    if(lightStatus.size() > 0) DEBUG_PRINTLN(lightStatus.size());
    for(int i = 0; i < lightStatus.size(); i++){
      String debugLine = String("") + lightStatus.get(i).first + " " + lightStatus.get(i).second + ",";
      DEBUG_PRINT(debugLine);
    }
    if(lightStatus.size() > 0) DEBUG_PRINTLN("");
#endif
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
  runThread.setInterval(1);

  threadController.add(&updateThread);
  threadController.add(&runThread);
}


void loop() {
  threadController.run();
}


