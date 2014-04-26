#define BUTTON_PIN 10
#define BUTTON_PRESS LOW //used to set high/low for press state

int buttonState = LOW;
int lastButtonState = LOW;
int lastDebounceState = LOW;

long debounceDelay = 50;
long lastDebounceTime = 0;

int val = LOW;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("PC Pedal");
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  val = digitalRead(BUTTON_PIN);
  
  if (val != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonState = val;
    
    if (buttonState != lastDebounceState) {
      if (buttonState == BUTTON_PRESS) {
          Serial.println("ON");
      }
      else {
        Serial.println("OFF");
      }
    }
    lastDebounceState = buttonState;
  }
  
  lastButtonState = val;
}

