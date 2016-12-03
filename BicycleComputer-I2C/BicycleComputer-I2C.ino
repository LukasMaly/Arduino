// include the library code:
#include <LiquidCrystal_I2C.h>

// To monitor the output
//#define SERIAL_DEBUG 1

// Set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// this constant won't change:
const int sensorPin = 2;     // the pin that the phototransistor is attached to
const float wheelC = 2.123;  // circumference of wheel [m]
const int samplingT = 3;     // sampling interval [s]

// Variables will change:
long counter = 0;            // counter for the number of samples
long lastCounter = 0;        // last interval counter value
long lastTime = millis();    // last interval time
int sensorState = 0;         // current state of the button
int lastsensorState = 0;     // previous state of the button

const int sensorThreshold = 100;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin();
  lcd.backlight();
  // Print a message to the LCD.
  lcd.print("Distnace: Speed:");
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize digital pin as an input.
  pinMode(sensorPin, INPUT);
  // initialize serial communication:
#ifdef SERIAL_DEBUG
    Serial.begin(9600);
#endif
}


void loop() {
  // read the pushbutton input pin:
  sensorState = digitalRead(sensorPin);
  
  // compare the sensorState to its previous state
  if (sensorState != lastsensorState) {
    // if the state has changed, increment the counter
    if (sensorState == LOW) {
      // if the current state is HIGH then the button
      // wend from off to on:
      counter++;
      digitalWrite(LED_BUILTIN, HIGH);
      delay(50);
    }
//    // Delay a little bit to avoid bouncing
//    delay(50);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW); 
  }

  // save the current state as the last state,
  //for next time through the loop
  lastsensorState = sensorState;

  if (millis() - lastTime >= samplingT * 1000) {
//    Serial.print("Mileage: ");
//    Serial.print(counter * wheelC / 1000);
//    Serial.println("km");
//  
//    Serial.print("Speed: ");
//    Serial.print(((counter - lastCounter) * wheelC)/float(samplingT) * 3.6);
//    Serial.println("km/h");
//    Serial.println();

    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(counter * wheelC / 1000);
    lcd.setCursor(10, 1);
    lcd.print(((counter - lastCounter) * wheelC)/float(samplingT) * 3.6);
  
    lastCounter = counter;
    lastTime = millis();
  }
  
#ifdef SERIAL_DEBUG
    Serial.print("Read ");
    Serial.println(sensorValue);
    delay(50);
#endif
}






