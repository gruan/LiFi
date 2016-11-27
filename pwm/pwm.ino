
#include "SymbolEncode.h"
#include "TransmissionEncode.h"

#define LED 9 // the PWM pin the LED is attached to

#define   BRIGHTNESS_ON 255
#define   BRIGHTNESS_REP 150
#define   BRIGHTNESS_OFF 50
#define   ERR_BRIGHTNESS 5
#define   NO_POWER_BRIGHTNESS 0

#define   SPECIAL_CHAR 251  // Indicates that no data has yet been read

#define   CALIBRATION_DELAY 200
#define   TRANSMISSION_DELAY 500 // 200

#define   CALIBRATE_ENABLED false

// Setup global variables
char currBit = SPECIAL_CHAR;  // Each bit is encoded as a string.
char lastBit = SPECIAL_CHAR;

char bitstring[8];

TransmissionEncode encoder(BRIGHTNESS_ON, BRIGHTNESS_REP, BRIGHTNESS_OFF, ERR_BRIGHTNESS, NO_POWER_BRIGHTNESS, SPECIAL_CHAR);

// the setup routine runs once when you press reset:
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
  // 0101010010010100
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

// the loop routine runs over and over again forever:
void loop() {
  if (Serial.available() > 0) {
    SymbolEncode::charToBitstring(Serial.read(), bitstring);

    for (int i = 0; i < 8; ++i) {
      currBit = bitstring[i];
      // analogWrite(LED, encoder.noEncoding(currBit));
      // analogWrite(LED, encoder.nrziEncoding(currBit, lastBit));
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
