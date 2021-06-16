
// Don't change these ////////////////////////////////////////////////////////////////////////////
const int ledPin1 = 3;    // LED 1
const int ledPin2 = 9;    // LED 2

unsigned long startTime = 0;
unsigned long endTime = 0;

int brightness1 = 0;      // LED 1
int brightness2 = 0;      // LED 2

// Change these ///////////////////////////////////////////////////////////////////////////////////
int brightnessMax1 = 125; // (0 - 255) LED 1 (For EVERLIGHT, keep to around 125)
int brightnessMax2 = 30;  // (0 - 255) LED 2

int brightnessMin1 = 0;   // (0 - 255) LED 1
int brightnessMin2 = 0;   // (0 - 255) LED 2

int fadeSpeed1 = 40;      // LED 1 Fade Speed
int fadeSpeed2 = 5;       // LED 2 Fade Speed

int ledOnHold = 2000;     // How long LEDs are held ON
int ledOffHold = 2000;    // How long LEDs are held OFF

int ledTime = 500;        // (milliseconds) Total time allowed for LEDs fade transition


// SETUP /////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);        // Declare pin 3 to be an output
  pinMode(ledPin2, OUTPUT);        // Declare pin 9 to be an output
  Serial.begin(9600);
}

// MAIN /////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  ledsFadeOn();
  ledsFadeOff();
}

// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////
void ledsFadeOn() {
  startTime = millis();
  endTime = startTime + ledTime;
  
  while (startTime <= endTime) {
    startTime = millis();                           // Set startTime equal to total program run time
    if (brightness1 <= brightnessMax1) {            // Increase LED 1 brightness until equal to LED 1 brightnessMax
      brightness1 = brightness1 + fadeSpeed1;      
      if (brightness1 > 255) { brightness1 = 255; } // Flicker protection
      analogWrite(ledPin1, brightness1);            
    }
    if (brightness2 <= brightnessMax2) {            // Increase LED 2 brightness until equal to LED 2 brightnessMax
      brightness2 = brightness2 + fadeSpeed2;
      if (brightness2 > 255) { brightness2 = 255; } // Flicker protection
      analogWrite(ledPin2, brightness2);
    }
    delay(30);                                      // Wait for fade
  }
  delay(ledOnHold);                                 // Hold LEDs ON for specified time
}

void ledsFadeOff() {  
  startTime = millis();
  endTime = startTime + ledTime;
  
  while (startTime <= endTime) {
    startTime = millis();                       // Set startTime equal to total program run time
    if (brightness1 >= brightnessMin1) {        // Decrease LED 1 brightness until equal to LED 1 brightnessMin
      brightness1 = brightness1 - fadeSpeed1;   
      if (brightness1 < 0) { brightness1 = 0; } // Flicker protection
      analogWrite(ledPin1, brightness1);
    }
    if (brightness2 >= brightnessMin2) {        // Decrease LED 2 brightness until equal to LED 2 brightnessMin
      brightness2 = brightness2 - fadeSpeed2;   
      if (brightness2 < 0) { brightness2 = 0; } // Flicker protection
      analogWrite(ledPin2, brightness2);
    }
    delay(30);                                  // Wait for fade
  }
  delay(ledOffHold);                            // Hold LEDs OFF for specified time
}
