#include "pitches.h"
//#define NOTE_C4  262

const int buttonpin = 7;
const int ledpin = 6;
const int spkrpin = 5;

int lastButtonState = LOW;
int buttonState = LOW;
long lastdebouncetime = 0;
long debouncedelay = 50;

enum States { WAITING, STARTINPUT, PLAYINGTONE, COUNT };
int state = WAITING;

int delayTime = 0;
int tonePlayTime = 100;
int minDelay = 250;
int pressTime = 0;

const int note = NOTE_C4;

void setup()
{
  Serial.begin(9600);
  Serial.println("button app");
  pinMode(buttonpin, INPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(spkrpin, OUTPUT);
  
  digitalWrite(ledpin, HIGH);
  delay(tonePlayTime);
  digitalWrite(ledpin, LOW);
}

void loop()
{
  String str = "";
  str.reserve(200);
  boolean buttonpushed = false;
  
  int val = digitalRead(buttonpin);
  
  if (state != PLAYINGTONE)
  {
    if (val != lastButtonState)
    {
      lastdebouncetime = millis();
    }
    if ((millis() - lastdebouncetime) > debouncedelay)
    {
      buttonState = val;
      if (buttonState == HIGH) {
        buttonpushed = true;
      }
    }
    if (buttonpushed)
    {
      if (state == WAITING)
      {
        state = STARTINPUT;
        delayTime = millis();
        pressTime = millis();
        str += "starting input time: ";
        str += delayTime;
        Serial.println(str);
        digitalWrite(ledpin, HIGH);
        delay(tonePlayTime);
        digitalWrite(ledpin, LOW);
      }
      else if (state == STARTINPUT)// && (millis()-pressTime) > minDelay)
      {
        state = PLAYINGTONE;
        delayTime = millis() - delayTime;
        str += "delay time: ";
        str += delayTime;
        Serial.println(str);
      }
    }
  }
  if (state == PLAYINGTONE)
  {
    str += "playing tone";
    Serial.println(str);
    digitalWrite(ledpin, HIGH);
    tone(spkrpin, note, tonePlayTime);
    //delay(tonePlayTime);
    digitalWrite(ledpin, LOW);
    delay(delayTime);
  }
  lastButtonState = val;
}
