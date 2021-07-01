
// Don't change these ////////////////////////////////////////////////////////////////////////////
const int ledPin1 = 3;    // LED 1
const int ledPin2 = 9;    // LED 2

unsigned long startTime = 0;
unsigned long endTime = 0;
unsigned long savedByte = 0;

int brightness1 = 0;      // LED 1 Brightness
int brightness2 = 0;      // LED 2 Brightness

int cycleCount = 4;       // How many times the LED fades On/Off
int cycleEnd = 1;         // Prompt user for Input if set to 1

// Change these ///////////////////////////////////////////////////////////////////////////////////
int brightnessMax1 = 32; // (0 - 255) LED 1 (For EVERLIGHT, keep to around 125)
int brightnessMax2 = 46;  // (0 - 255) LED 2

int brightnessMin1 = 0;   // (0 - 255) LED 1
int brightnessMin2 = 0;   // (0 - 255) LED 2

int fadeSpeed1 = 10;      // LED 1 Fade Speed
int fadeSpeed2 = 10;       // LED 2 Fade Speed

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
  if (cycleEnd == 1) {
    // Program Start
    printMenu();
    getMenuSelection();
  }
}

// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////


int getUserInput() {
  // Read user input
  savedByte = Serial.available();
  while (Serial.available() == savedByte) {
    // Wait for User to input cycle count
  }
  int userInput = Serial.parseInt();
  return userInput;
}


void printMenu() {
  Serial.println();
  Serial.println("/////////////////////// MENU /////////////////////////");
  Serial.println();
  Serial.println("Select a menu item (1-11) or press ENTER to Start:");
  Serial.println();
  Serial.println("------------------------------------------------------");
  Serial.print("1.  LED 1, Min Brightness = ");
  Serial.println(brightnessMin1);
  Serial.print("2.  LED 1, Max Brightness = ");
  Serial.println(brightnessMax1);
  Serial.print("3.  LED 1,     Fade Speed = ");
  Serial.println(fadeSpeed1);
  Serial.println("------------------------------------------------------");
  Serial.print("4.  LED 2, Min Brightness = ");
  Serial.println(brightnessMin2);
  Serial.print("5.  LED 2, Max Brightness = ");
  Serial.println(brightnessMax2);
  Serial.print("6.  LED 2,     Fade Speed = ");
  Serial.println(fadeSpeed2);
  Serial.println("------------------------------------------------------");
  Serial.print("7.  How long LEDs are held ON  = ");
  Serial.print(ledOnHold);
  Serial.println(" ms");
  Serial.print("8.  How long LEDs are held OFF = ");
  Serial.print(ledOffHold);
  Serial.println(" ms");
  Serial.print("9.  Time allowed for LEDs fade transition = ");
  Serial.print(ledTime);
  Serial.println(" ms");
  Serial.println("------------------------------------------------------");
  Serial.print("10. LED ON/OFF Cycles = ");
  Serial.println(cycleCount);
  Serial.println("------------------------------------------------------");
  Serial.println("11. RESET TO DEFAULTS");
  Serial.println("------------------------------------------------------");
  Serial.println();
}


void getMenuSelection() {
  int menuSelection = getUserInput();
  int newValue;
  if (menuSelection == 0) {
    Serial.println("<<<<<<<<<<<<<<<<<<<< TEST START >>>>>>>>>>>>>>>>>>>>>>");
    Serial.println();
    startCycle();
  } else if (menuSelection == 1) {
    Serial.print(">>> 1. Input value (0-255) for LED 1's MIN BRIGHTNESS: ");
    newValue = getUserInput();
    Serial.println(newValue);
    brightnessMin1 = newValue;
    ledsOnMin();
  } else if (menuSelection == 2) {
    Serial.print(">>> 2. Input value (0-255) for LED 1's MAX BRIGHTNESS: ");
    newValue = getUserInput();
    Serial.println(newValue);
    brightnessMax1 = newValue;
    ledsOnMax();
  } else if (menuSelection == 3) {
    Serial.print(">>> 3. Input value for LED 1's FADE SPEED: ");
    newValue = getUserInput();
    Serial.println(newValue);
    fadeSpeed1 = newValue;
  } else if (menuSelection == 4) {
    Serial.print(">>> 4. Input value (0-255) for LED 2's MIN BRIGHTNESS: ");
    newValue = getUserInput();
    Serial.println(newValue);
    brightnessMin2 = newValue;
    ledsOnMin();
  } else if (menuSelection == 5) {
    Serial.print(">>> 5. Input value (0-255) for LED 2's MAX BRIGHTNESS: ");
    newValue = getUserInput();
    Serial.println(newValue);
    brightnessMax2 = newValue;
    ledsOnMax();
  } else if (menuSelection == 6) {
    Serial.print(">>> 6. Input value for LED 2's FADE SPEED: ");
    newValue = getUserInput();
    Serial.println(newValue);
    fadeSpeed2 = newValue;
  } else if (menuSelection == 7) {
    Serial.print(">>> 7. Specify how long (ms) LEDS are held ON: ");
    newValue = getUserInput();
    Serial.println(newValue);
    ledOnHold = newValue;
    if (ledOnHold == 7777) {
      ledsOnMax();
    }
  } else if (menuSelection == 8) {
    Serial.print(">>> 8. Specify how long (ms) LEDS are held OFF: ");
    newValue = getUserInput();
    Serial.println(newValue);
    ledOffHold = newValue;
  } else if (menuSelection == 9) {
    Serial.print(">>> 9. Specify how much time (ms) is allowed for LEDs fade transition: ");
    newValue = getUserInput();
    Serial.println(newValue);
    ledTime = newValue;
  } else if (menuSelection == 10) {
    Serial.print(">>> 10. Specify how many LED ON/OFF Cycles: ");
    newValue = getUserInput();
    Serial.println(newValue);
    cycleCount = newValue;
  } else if (menuSelection == 11) {
    resetToDefaults();
    Serial.println();
    Serial.println("DEFAULT VALUES RESTORED");
    Serial.println();
  } else {
    Serial.println();
    Serial.println("Value out of range, pick a number between 1-11:");
    Serial.println();
  }
}


void startCycle() {
    // Initiates ON/OFF cycle
    Serial.print("Cycles = ");
    Serial.println(cycleCount);
    Serial.println();
  for (int counter = 1; counter <= cycleCount; counter++) {
    // Prints LED status to Serial Monitor
    Serial.print("Cycle #");
    Serial.print(counter);
    Serial.print("...ON");
    ledsFadeOn();
    Serial.println("...OFF");
    ledsFadeOff();
  }
  cycleEnd = 1;
  Serial.println();
  Serial.println("Cycle count reached.");
  Serial.println();
  Serial.println("<<<<<<<<<<<<<<<<<<<<  TEST END  >>>>>>>>>>>>>>>>>>>>>>");
}


void resetToDefaults() {
  // Reset to Default Values from Main Menu
  brightnessMax1 = 32; // LED 1
  brightnessMax2 = 46; // LED 2
  brightnessMin1 = 0;  // LED 1
  brightnessMin2 = 0;  // LED 2
  fadeSpeed1 = 10;     // LED 1
  fadeSpeed2 = 10;     // LED 2
  ledOnHold = 2000;    // Time LEDs stay ON
  ledOffHold = 2000;   // Time LEDs stay OFF
  ledTime = 500;       // (ms) Time allowed for fading
  cycleCount = 4;      // (ON -> OFF) = 1 Cycle
}


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


void ledsOnMax() {
  // Used to hold LEDs at maximum brightnes
  analogWrite(ledPin1, brightnessMax1);
  analogWrite(ledPin2, brightnessMax2);
}


void ledsOnMin() {
  // Used to hold LEDs at mininum brightness
  analogWrite(ledPin1, brightnessMin1);
  analogWrite(ledPin2, brightnessMin2);
}


void clearSerialMonitor() {
  // Will be used to clear Serial Monitor output
  // Untested as of 7/1/20221
  while (i < 10) {
    Serial.println();
    i++;
  }
}


void ledsFadeOff() {  
  startTime = millis();
  endTime = startTime + ledTime;
  
  while (startTime <= endTime) {
    startTime = millis();                       
    if (brightness1 >= brightnessMin1) {        
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
