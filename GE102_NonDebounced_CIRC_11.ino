/*     -----------------------------------------------------------
 *     | JAMES PERRIN GE102   Week 7        1.0                  |
 *     -----------------------------------------------------------
 *
 *      Forward and reverse controller using arduino and relay:
 *      
 *      Allows for forward and reverse control (using a button) of a toy motor as well as a power on and off button. Includes red Led power indicator
 *      as well as two leds to indicate whether the motor is currenty running clockwise or counterclockwise.
 *
 *      PRESENT ISSUES:
 *      
 *      1. power button not debounced but I havent had any serious issues thus far...
 *      2. Transistor base control connected to motorPin 5 needs a capacitor 100 uF or else relay buzzes momentarily when power is applied
 *      3. diode snubs EMF each time motor direction is changed (every time the button is pressed); when I did not have power control transistor hooked up it only flashed when 
 *         power was applied (once every two clicks of the button), I am not sure what the ramifications of this are.
 *
 */




#define buttonPin 2            // starts/stops flow to relay control transistor
#define buttonPower 4          // Power button
#define motorPin 5            // Whatever pin you want to control your relay
#define powerPin 10          // Controls transistors breadboard ground flow (basically cuts off breadboard from ground when there isnt any current).


bool currentButton = LOW;             // True or False
bool currentButtonTwo = LOW;
bool lastButton = LOW;              // True or False
bool lastButtonTwo = LOW;            // True or False


int motorState = 0;               // The default motor value
int powerState = 0;               // 
int voltageOn = 255;              // Activates power in digital pins 1.5V  40mA



void setup() {                      // Stuff that we want to get run once and big in the bigger scope of things
  Serial.begin(9600);                     // Useful for debugging
  pinMode(buttonPin, INPUT);                 // Uhh setting pinmode to input fo the button
  pinMode(buttonPower, INPUT);
  pinMode(motorPin, OUTPUT);                // setting mot pin to output
  pinMode(powerPin, OUTPUT);
 
}

  boolean debounce(boolean last)                   // My debouncing attempt
  {
    boolean current = digitalRead(buttonPin);
    if (last != current)
    {
      delay(5);
      current = digitalRead(buttonPin);
    }
    return current;
  }

void loop() {                                                 //     majority of whats going on

  currentButton = debounce(lastButton);                      // runs debounce routine
  currentButtonTwo = digitalRead(buttonPower);

  if (lastButton == LOW && currentButton == HIGH) {            // ** so that the button doesnt double register... I think...

   

             

      if (motorState <= 255) {                                  // Will raise voltage if voltage on motor is still <= 255
         motorState = motorState + voltageOn;

         Serial.println(motorState);                            // For my debugging purposes
         delay(50);
         Serial.println(buttonPin);                              // Same ^
         delay(50);  
      }

      if (motorState > 255) {          // turns off LED AND motor if motor is greater than 255 volts
        motorState = 0;

        Serial.println(motorState);      // For my debugging purposes
        delay(50);
        Serial.println(buttonPin);         // Same ^
        delay(50);
       } 
  }

 


/*
 * A whole new block of code for second button here
 * 
 */


 if (currentButtonTwo != lastButtonTwo) {            // ** so that the button doesnt double register... I think...



 if (currentButtonTwo == HIGH) {                // The meat and potatoes of the opperation, Starts the next gear if the gear is still < 5

      if (powerState <= 255) {                 // Will raise voltage if voltage on motor is still <= 255
        powerState = powerState + voltageOn;

        Serial.println(powerState);             // For my debugging purposes
        delay(50);
        Serial.println(buttonPower);            // Same ^
        delay(50);
        
      }

      if (powerState > 255) {                   // turns off LED AND motor if motor is greater than 255 volts
        powerState = 0;

          Serial.println(powerState);            // For my debugging purposes
           delay(50);
           Serial.println(buttonPower);         // Same ^
           delay(50);
        
      }
     
    }
  }



  analogWrite(motorPin, motorState);           // Puts our (at the moment) hypothetical nonsense into the physical realm
  analogWrite(powerPin, powerState);

  lastButton = currentButton;                  //  ties back to **
  lastButtonTwo = currentButtonTwo;            //  ties back to **
}
