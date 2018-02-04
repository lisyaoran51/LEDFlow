// Lab12 使用兩顆 74HC595 和三支腳位控制 16 顆 LED

// 接 74HC595 的 ST_CP (pin 12,latch pin)
int latchPin = 8;
// 接 74HC595 的 SH_CP (pin 11, clock pin)
int clockPin = 12;
// 接 74HC595 的 DS (pin 14)
int dataPin = 11;

void setup() {
  Serial.begin(9600);
  // 將 latchPin, clockPin, dataPin 設置為輸出
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop1(){
  float a = 1.234;
  Serial.println(a);
  Serial.println(String(a,3));
  long b = 1.2345L;
  a = b;
  Serial.println(a);
  Serial.println(String(a,3));
  
}

void loop() {

        
  for (int led = 0; led < 32; led++) {
    int numberToDisplay  = 1 << led;
    byte high_Byte = highByte(numberToDisplay);
    byte low_Byte = lowByte(numberToDisplay);
    
    for(int i = 0; i < 11; i++ ){
      // 送資料前要先把 latchPin 拉成低電位
      digitalWrite(latchPin, LOW);
      if(i > 7){
        shiftOut(dataPin, clockPin, MSBFIRST, 1<<(i-8));//pow(2,i-8+1));
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
      }
      else{
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, 1<<i);//pow(2,i));
      }

      // 先送高位元組 (Hight Byte), 給離 Arduino 較遠的那顆 74HC595
      //shiftOut(dataPin, clockPin, MSBFIRST, high_Byte);  
      // 再送低位元組 (Low Byte), 給離 Arduino 較近的那顆 74HC595
      if(led<8){
        shiftOut(dataPin, clockPin, MSBFIRST, 0); 
        shiftOut(dataPin, clockPin, MSBFIRST, 0); 
        shiftOut(dataPin, clockPin, MSBFIRST, 0); 
        shiftOut(dataPin, clockPin, MSBFIRST, 1<<led); 
      }
      else if(led<16){
        shiftOut(dataPin, clockPin, MSBFIRST, 0); 
        shiftOut(dataPin, clockPin, MSBFIRST, 0);  
        shiftOut(dataPin, clockPin, MSBFIRST, 1<<(led-8)); 
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
      }
      else if(led<24){
        shiftOut(dataPin, clockPin, MSBFIRST, 0);  
        shiftOut(dataPin, clockPin, MSBFIRST, 1<<(led-16)); 
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
      }else{
        shiftOut(dataPin, clockPin, MSBFIRST, 1<<(led-24)); 
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
      }
      // 送完資料後要把 latchPin 拉回成高電位
      digitalWrite(latchPin, HIGH);
     
      //delay(30);
    }
    
   
    
  }
}
