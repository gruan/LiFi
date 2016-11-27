
#include "SymbolEncode.h"
#include "TransmissionEncoder.h"

#define LED 9 // the PWM pin the LED is attached to

#define   BRIGHTNESS_ON 255
#define   BRIGHTNESS_REP 150
#define   BRIGHTNESS_OFF 50
#define   ERR_BRIGHTNESS 5
#define   NO_POWER_BRIGHTNESS 0

#define   SPECIAL_CHAR    251    // Indicates that no data has yet been read
#define   BEGIN_MES       123    // Indicates the beginning of a message {
#define   CALIB_CHAR      126    // Indicates that calibration should be performed ~
#define   END_MES         125    // Indicates the ending of a message }


#define   CALIBRATION_DELAY 200
#define   TRANSMISSION_DELAY 200 // 200

#define   CALIBRATE_ENABLED false

// Setup global variables
char currBit = SPECIAL_CHAR;  // Each bit is encoded as a string.
char lastBit = SPECIAL_CHAR;

TransmissionEncoder encoder(BRIGHTNESS_ON, BRIGHTNESS_REP, BRIGHTNESS_OFF, ERR_BRIGHTNESS, NO_POWER_BRIGHTNESS, SPECIAL_CHAR);
char bitstring[8];

char charRead;
bool isMessageOpen = false;

void setup() {
  // declare pin 9 to be an output:
  pinMode(LED, OUTPUT);

  // Begin Serial communication.
  Serial.begin(9600);
  Serial.setTimeout(1);

  // Calibrate receiver sensor
  if (CALIBRATE_ENABLED)
    calibrate(CALIBRATION_DELAY);
}

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

void loop() {
  if (Serial.available() > 0) {
    charRead = Serial.read();

    if (charRead == BEGIN_MES) {
      Serial.println("Message begins");
      isMessageOpen = true;
      return;
    }
    
    if (charRead == CALIB_CHAR) {
      Serial.println("Calibrate!");
      calibrate(CALIBRATION_DELAY);
      return;
    } 
    
    if (charRead == END_MES) {
      Serial.println("Message ends");
      isMessageOpen = false;
      return;
    }

    if (!isMessageOpen)
      return;
    
    SymbolEncode::charToBitstring(charRead, bitstring);

    for (int i = 0; i < 8; ++i) {
      currBit = bitstring[i];
      analogWrite(LED, encoder.ruanEncoding(currBit, lastBit));

      lastBit = currBit;
      
      delay(TRANSMISSION_DELAY);
    }
  }
  else {
    analogWrite(LED, 0);
    delay(TRANSMISSION_DELAY);
  }
}
