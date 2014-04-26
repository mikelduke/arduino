#include <Servo.h> 
 
Servo servo1;
Servo servo2;
 

int val = 0;
int max = 950;
int v = 100;
 
void setup() 
{ 
  Serial.begin(9600);
  servo1.attach(9);  //horizontal red wire in cable
  servo2.attach(10); //vertical white wire
} 
 
void loop() 
{ 
  String out = "";
  int valx = analogRead(0);
  out += valx;
  Serial.println(valx);
  
  if (valx > ((max/2)+v)) servo2.write(0);
  else if (valx < ((max/2)-v)) servo2.write(180);
  else servo2.write(90);
  
  int valy = analogRead(1);
  if (valy > ((max/2)+v)) servo1.write(0);
  else if (valy < ((max/2)-v)) servo1.write(180);
  else servo1.write(90);
}

