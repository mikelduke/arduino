/*************************************************** 
  This is a test example for the Adafruit Trellis w/HT16K33

  Designed specifically to work with the Adafruit Trellis 
  ----> https://www.adafruit.com/products/1616
  ----> https://www.adafruit.com/products/1611

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  MIT license, all text above must be included in any redistribution
 ****************************************************/
 
#include <Wire.h>
#include "Adafruit_Trellis.h"
#include <SoftwareSerial.h>

#define MOMENTARY 0
#define LATCHING 1
// set the mode here
#define MODE MOMENTARY 

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_Trellis matrix1 = Adafruit_Trellis();
Adafruit_Trellis matrix2 = Adafruit_Trellis();
Adafruit_Trellis matrix3 = Adafruit_Trellis();

Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1, &matrix2, &matrix3);

#define NUMTRELLIS 4
#define numKeys (NUMTRELLIS * 16)

#define INTPIN A2

SoftwareSerial softSerial(3, 2); // RX, TX


void setup() {
  Serial.begin(9600);
  Serial.println("Trellis Demo");

  // INT pin requires a pullup
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  
  //trellis.begin(0x70);  // only one
  trellis.begin(0x70, 0x71, 0x72, 0x73);

  // light up all the LEDs in order
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(10);
  }
  // then turn them off
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(10);
  }
  
  softSerial.begin(31250);
}


void loop() {
  delay(30); // 30ms delay is required, dont remove me!
  
  if (MODE == MOMENTARY) {
    // If a button was just pressed or released...
    if (trellis.readSwitches()) {
      // go through every button
      for (uint8_t i=0; i<numKeys; i++) {
	// if it was pressed, turn it on
	if (trellis.justPressed(i)) {
	  Serial.print("v"); Serial.println(i);
	  trellis.setLED(i);
          sendMidiNote(mapButton(i));
	} 
	// if it was released, turn it off
	if (trellis.justReleased(i)) {
	  Serial.print("^"); Serial.println(i);
	  trellis.clrLED(i);
	}
      }
      // tell the trellis to set the LEDs we requested
      trellis.writeDisplay();
    }
  }

  if (MODE == LATCHING) {
    // If a button was just pressed or released...
    if (trellis.readSwitches()) {
      // go through every button
      for (uint8_t i=0; i<numKeys; i++) {
        // if it was pressed...
	if (trellis.justPressed(i)) {
	  Serial.print("v"); Serial.println(i);
	  // Alternate the LED
	  if (trellis.isLED(i))
	    trellis.clrLED(i);
	  else
	    trellis.setLED(i);
        } 
      }
      // tell the trellis to set the LEDs we requested
      trellis.writeDisplay();
    }
  }
}

/* changes below added by mld www.mikelduke.com */

// remaps buttom numbers to go 0-63 from bottom left to upper right
uint8_t mapButton(uint8_t button) {
  if (button >= 12 && button < 16)     button -= 12;  //bottom left trellis  0
  else if (button >= 8 && button < 12) ;              //button is right      8
  else if (button >= 4 && button < 8)  button += 12;  //                    16
  else if (button >= 0 && button < 4)  button += 24;  //                    24
  
  else if (button >= 28 && button < 32) button -= 24; //bottom right trellis 4
  else if (button >= 24 && button < 28) button -= 12; //                    12
  else if (button >= 20 && button < 24) ;             //button is right     20
  else if (button >= 16 && button < 20) button += 12; //                    28
  
  else if (button >= 44 && button < 48) button -= 12; //top right           32
  else if (button >= 40 && button < 44) ;             //                    40
  else if (button >= 36 && button < 40) button += 12; //                    48
  else if (button >= 32 && button < 36) button += 24; //                    56
  
  else if (button >= 60 && button < 64) button -= 24; //                    36
  else if (button >= 56 && button < 60) button -= 12; //                    44
  else if (button >= 52 && button < 56) ;             //                    52
  else /*  button >= 48 && button < 52*/button += 12; //                    60
  
  /*Serial.print("Mapped button: ");
  Serial.println(button);*/

  return button;
}

//output midi note based on button number
void sendMidiNote(uint8_t note) {
  note += 0x1E;
  midiCommand(0x90, note, 0x45); //controller 1, pitch, medium velocity
}

void midiCommand(int cmd, int pitch, int velocity) {
  softSerial.write(cmd);
  softSerial.write(pitch);
  softSerial.write(velocity);
}

