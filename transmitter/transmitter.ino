#include <HashMap.h>
#include "SymbolEncoder.h"
#include "TransmissionEncoder.h"

#define LED 9 // the PWM pin the LED is attached to

#define   BRIGHTNESS_ON  255
#define   BRIGHTNESS_REP 150
#define   BRIGHTNESS_OFF 0
#define   ERR_BRIGHTNESS 5
#define   NO_POWER_BRIGHTNESS 0

#define   INITIAL_CHAR    251    // Indicates that no data has yet been read
#define   BEGIN_MES       123    // Indicates the beginning of a message {
#define   CALIB_CHAR      126    // Indicates that calibration should be performed ~
#define   END_MES         125    // Indicates the ending of a message }

#define   PREAMBLE        "1100110011"
#define   PREAMBLE_LEN    10
#define   POSTAMBLE       "0011001100"
#define   POSTAMBLE_LEN   10
#define   CARRIER        "1010101010"
// #define   IDLE_MSG "0000000000"
#define   CARRIER_LEN    10

#define   CALIBRATION_DELAY 60
#define   TRANSMISSION_DELAY 4

// Setup global variables
char currBit = INITIAL_CHAR;  // Each bit is encoded as a string.
char lastBit = INITIAL_CHAR;

TransmissionEncoder transmissionEncoder(BRIGHTNESS_ON, BRIGHTNESS_REP, BRIGHTNESS_OFF, ERR_BRIGHTNESS, NO_POWER_BRIGHTNESS, INITIAL_CHAR);
char bitstring[8];

SymbolEncoder symbolEncoder;

char charRead;
bool isMessageOpen = false;

void test() {
  // Tests the bit sequence: 0101010010010100
  int len = 17;
  int test[len] = { BRIGHTNESS_ON, BRIGHTNESS_REP, BRIGHTNESS_ON, BRIGHTNESS_REP,
                    BRIGHTNESS_OFF, BRIGHTNESS_ON, BRIGHTNESS_OFF, BRIGHTNESS_REP,
                    BRIGHTNESS_ON, BRIGHTNESS_OFF, BRIGHTNESS_REP, BRIGHTNESS_ON,
                    BRIGHTNESS_REP, BRIGHTNESS_ON, BRIGHTNESS_OFF, BRIGHTNESS_REP,
                    BRIGHTNESS_OFF
                  };

  int i;
  for (i = 0; i < len; ++i) {
    analogWrite(LED, test[i]);
    delay(TRANSMISSION_DELAY);
  }
}

void calibrate(int delayTime) {
  int len = 4;
  int calibrations[len] = { BRIGHTNESS_OFF, BRIGHTNESS_REP, BRIGHTNESS_ON, NO_POWER_BRIGHTNESS };
  int repetitions = 10;

  int i, j;
  for (i = 0; i < len; ++i) {
    for (j = 0; j < repetitions; ++j) {
      analogWrite(LED, calibrations[i]);
      delay(delayTime);
    }
  }
}

void transmitMessage(const char * message, int messageLen) {
  for (int i = 0; i < messageLen; ++i) {
    currBit = message[i];
    analogWrite(LED, transmissionEncoder.noEncoding(currBit));
    delay(TRANSMISSION_DELAY);
  }
}

void setup() {
  // declare pin 9 to be an output:
  pinMode(LED, OUTPUT);

  // Begin Serial communication.
  Serial.begin(9600);
  Serial.setTimeout(1);

}

void loop() {
  /*
  for (int i = 0; i < 300; ++i) {
    transmitMessage(CARRIER, CARRIER_LEN);    
  }
  delay(500);
  transmitMessage(CARRIER, CARRIER_LEN);
  transmitMessage(PREAMBLE, PREAMBLE_LEN);
  transmitMessage(CARRIER, CARRIER_LEN);
  while(1);
  */

  
  if (Serial.available() > 0) {
    charRead = Serial.read();

    // Send pre-amble
    if (charRead == BEGIN_MES) {
      Serial.println("Message begins");
      isMessageOpen = true;

      transmitMessage(PREAMBLE, PREAMBLE_LEN);
      return;
    }

    if (charRead == CALIB_CHAR) {
      Serial.println("Calibrate!");
      calibrate(CALIBRATION_DELAY);
      return;
    }

    // Send post-amble
    if (charRead == END_MES) {
      Serial.println("Message ends");
      isMessageOpen = false;

      // Set it back to the initial state when no message was being sent
      currBit = INITIAL_CHAR;
      lastBit = INITIAL_CHAR;

      transmitMessage(POSTAMBLE, POSTAMBLE_LEN);
      return;
    }

    // If pre-amble not sent, don't send.
    if (!isMessageOpen)
      return;

    // Send characters

    const char * firstHalf = symbolEncoder.charToBitstring4B5BFirstHalf(charRead);
    const char * secondHalf = symbolEncoder.charToBitstring4B5BSecondHalf(charRead);

    transmitMessage(firstHalf, 5);
    transmitMessage(secondHalf, 5);
  }
  else {
    transmitMessage(CARRIER, CARRIER_LEN);
  }
}

