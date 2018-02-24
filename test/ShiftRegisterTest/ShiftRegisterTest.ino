#include "ShiftRegisterController.h"
#include <LinkedList.h>


ShiftRegisterController shiftRegisterController = ShiftRegisterController(8, 12, 11, 32, 11); // latch, clock, data, keyAmount, ledLength
LinkedList<Pair> ledStatus = LinkedList<Pair>();

void setup() {
  Serial.begin(9600);
  
}

int i,j;
void loop() {
  Pair p;
    p.first = i;
    p.second = j;
    ledStatus.add(p);
  shiftRegisterController.Set(&ledStatus);
  for(int j = 0; j < 10; j++) shiftRegisterController.Run();
  //shiftRegisterController.Print();
  i++;
  //delay(1000);
  //ledStatus.clear();
  if(i == 32){
    
    ledStatus.clear();
    i=0;
    j++;
  }
}
