// AIM :- Wireless LED bulb dimmer using Radio frequency - ON/OFF/DIM via remote.

/* Components used :- Arduino Uno, two 237 ohm resistors, one blue and red led, breadboard, jumper wires, 10PCS TL1838 VS1838 Universal IR Infrared Receiver Sensor
                      and IR remote.
*/

#include <IRremoteInt.h> // using ir remote libraries
#include <IRremote.h>
int RECV_PIN = 6;     // declaring the pin for reciever
int BLUE_LED = 13;    // declaring the pin for blue led
int RED_LED = 12;     // declaring the pin for red led



IRrecv irrecv(RECV_PIN);  // function for ir sensor
decode_results results;   // function for decoding the buttons hexcode

void setup() {
                                // initialize the digital pin as an output.
  pinMode(RECV_PIN, INPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  irrecv.enableIRIn();        // Start the receiver
  Serial.begin(9600);
}
void loop() {
  int i = 0;                        // declaring the variables, initealising the int datatype of i to 0
  int unknownRemote;
  byte brightness;
  if (irrecv.decode(&results)) {    // manipulating the results
    if (Serial.available()) {
      brightness = Serial.read();        // controlling the brightness
      analogWrite (RECV_PIN, brightness);  // a an analog pin ( 6 in this case) is used for regulating the brightness
    }
    translateIR();
    unknownRemoter();

    irrecv.resume();         // Receive the next value

  }
}

void translateIR() //  takes action based on IR code received describing Car MP3 IR codes (which i had an access to)
{

  switch (results.value) {
    case 0xFFA25D:                           // these are the hex values
      Serial.println(" CH-            ");
      break;
    case 0xFF629D:
      Serial.println(" CH             ");
      break;
    case 0xFFE21D:
      Serial.println(" CH+            ");
      break;
    case 0xFF22DD:
      Serial.println(" blue LED off          ");
      digitalWrite(13, LOW);
      break;
    case 0xFF02FD:
      Serial.println(" blue LED on        ");
      digitalWrite(13, HIGH);
      break;
    case 0xFFC23D:
      Serial.println(" PLAY/PAUSE     ");
      break;
    case 0xFFE01F:
      Serial.println(" VOL-           ");
      break;
    case 0xFFA857:
      Serial.println(" VOL+           ");
      break;
    case 0xFF906F:
      Serial.println(" EQ             ");
      break;
    case 0xFF6897:
      Serial.println(" 0              ");
      break;
    case 0xFF9867:
      Serial.println(" 100+           ");
      break;
    case 0xFFB04F:
      Serial.println(" 200+           ");
      break;
    case 0xFF30CF:
      Serial.println(" 1              ");
      break;

    case 0xFF18E7:
      Serial.println(" 2              ");
      break;

    case 0xFF7A85:
      Serial.println(" 3              ");
      break;

    case 0xFF10EF:
      Serial.println(" 4              ");
      break;

    case 0xFF38C7:
      Serial.println(" 5              ");
      break;

    case 0xFF5AA5:
      Serial.println(" 6              ");
      break;

    case 0xFF42BD:
      Serial.println(" 7              ");
      break;

    case 0xFF4AB5:
      Serial.println(" 8              ");
      break;

    case 0xFF52AD:
      Serial.println(" 9              ");
      break;

    default:
      Serial.print(" unknown button   ");      // default case for unknown value
      Serial.println(results.value, HEX);

  }

  delay(500);


}

void unknownRemoter() {             // an undefined remote will handle the red led operations
  long RED_LED_OFF = 0xFF40BF;       /* hexcode
                                     values for that */
  long RED_LED_ON =  0xFF906F;
  long LAST_BUTTON = 0xFFD02F;

  if (results.value == RED_LED_OFF) {
    Serial.println ("Red led off");
    digitalWrite(12, LOW);
  }
  else if (results.value == RED_LED_ON )
  {
    Serial.println ("Red led on");
    digitalWrite(12, HIGH);
  }

}

/*  Logic :-

    In this program we try to make the led ON/OFF/DIM position.

    This can be achieved by -

    1. Using the 0-255 bytes signal mechanism for analog pin we can regulate the dimming mechanism for the led, in this case we used 6 th pin.
    2. We use two 237 Ohms of resistors in series with leds in order to protect them from substantial damage from the VCC supply.
    3. Manipulating the hexcode of the remote buttons to get the output on Serial Monitor.
    4. Also, here the red led blinks when the board is commected to the power( ensuring that circuit is complete, and bread board is connected ).
*/

/* Algorithm of code :-

    1. Start the program.
    2. Declare the variables and the pins used for initialising the setup and start the reciever.
    3. By using switch case, decision is made on serial monitor to print out-put.
    4. If statement decides to limit the brightness of the led.
    5. Loop will again start from step 3.
    6. If no vsalue is transmitted by the remote then, then the program will end. 
*/


// by - Dilpreet Singh Banga
//      17th March 2019
