#include <Servo.h> 
 
Servo servoX;
Servo servoY;
 

int val = 0;
int max = 950;
int v = 100;
 
void setup() 
{ 
  Serial.begin(115200);
  servoY.attach(9);  //horizontal red wire in cable
  servoX.attach(10); //vertical white wire
} 
 
void loop() 
{ 
  String out = "";
  int valx = analogRead(0);
  out += valx;
  //Serial.println(valx);
  
  if (Serial.available() > 0) {
    char charAr;
    //Serial.readBytes(charAr, 64);
    charAr = Serial.read();
    Serial.println(charAr);
    handleRead(charAr);
  }
  
  else {
    if (valx > ((max/2)+v)) servoX.write(0);
    else if (valx < ((max/2)-v)) servoX.write(180);
    else servoX.write(90);
    
    int valy = analogRead(1);
    if (valy > ((max/2)+v)) servoY.write(0);
    else if (valy < ((max/2)-v)) servoY.write(180);
    else servoY.write(90);
  }
}

void move(int x, int y, int ms) {
  servoX.write(x+90);
  servoY.write(y+90);
  delay(ms);
}

void handleRead(char charAr) {
  String out = "";
  if (charAr == 'm') {
    out += readMove();
  }
  Serial.println(out) ;
}

String readMove() {
  String out = "";
  int x = Serial.parseInt();
  int y = Serial.parseInt();
  int time = Serial.parseInt();
  out += x;
  out += ",";
  out += y;
  out += ",";
  out += time;
  move(x, y, time);
  return out;
}
