#include <Servo.h> 
 
Servo servo1;
Servo servo2;
 

int val;
 
void setup() 
{ 
  Serial.begin(9600);
  /*
  23s at 10
  servo1.attach(9);  //horizontal red wire in cable
  servo2.attach(10); //vertical white wire
  //servo2.attach(10);
  servo1.write(90);
  servo1.write(100);
  delay(23000);
  servo1.write(90);*/
  
  /*
  //1 full speed ish
  servo1.attach(9);  //horizontal red wire in cable
  servo1.write(90);
  servo1.write(180);
  delay(5600);
  servo1.write(90);*/
  
  /*
  // half circle
  servo1.attach(9);  //horizontal red wire in cable
  servo1.write(90);
  servo1.write(180);
  delay(2825);
  servo1.write(90);*/
  
  // quarter circle
  servo1.attach(9);  //horizontal red wire in cable
  servo1.write(90);
  servo1.write(180);
  delay(1475);
  servo1.write(90);
  
} 
 
void loop() 
{ 
  String out = "";
  int val = analogRead(0);
  out += val;
  Serial.println(val);
}

