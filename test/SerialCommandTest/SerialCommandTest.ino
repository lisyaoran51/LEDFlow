


#include <SoftwareSerial.h>
#include <SerialCommand.h>
SerialCommand sCmds;
bool r = false;

void setup() {

  digitalWrite(13,0);
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  sCmds.addCommand("Event", ReadSerial);
  sCmds.addCommand("PONG", pingHandler);
}

void pingHandler (const char *command) {
  digitalWrite(13,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  sCmds.readSerial();
}

void ReadSerial(const char *command){
  r = true;
  digitalWrite(13,1);
  char *arg;
  Serial.println("ReadSerial");
  arg = sCmds.next();    // Get the next argument from the SerialCommand object buffer
  if (arg != NULL)      // As long as it existed, take it
  {
    Serial.println(arg);
    arg = sCmds.next();
    if (arg != NULL) {
      Serial.println(arg);
      arg = sCmds.next();
    }
  }
}
