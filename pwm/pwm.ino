/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with 
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 This example code is in the public domain.
 */

int BRIGHTNESS_ON = 200;
int BRIGHTNESS_REP = 100;
int BRIGHTNESS_OFF = 50;
int ERR_BRIGHTNESS = 5;
int NO_DATA_BRIGHTNESS = 0;

int led = 9;           // the PWM pin the LED is attached to

int byteRead = -1;
int lastByteRead = -1;
bool repBrightnessFlag = true;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(1);

  calibrate(500);
}

void calibrate(int delayTime) {
  int len = 3;
  int calibrations[len] = { BRIGHTNESS_OFF, BRIGHTNESS_REP, BRIGHTNESS_ON };
  int repetitions = 10;

  int i, j;
  for (i = 0; i < len; ++i) {
    for (j = 0; j < repetitions; ++j) {
      analogWrite(led, calibrations[i]);
      delay(delayTime);
    }
  }
}

int noEncoding(char bit) {
  if (bit == '1') {
    return BRIGHTNESS_ON;
  } else if (bit == '0') {
    return BRIGHTNESS_OFF;
  } else {
    return ERR_BRIGHTNESS;
  }
}

int nrziEncoding(char currChar, char lastChar) {
  // No data has yet been received.
  if (currChar == -1)
    return NO_DATA_BRIGHTNESS;

  // Error. The character should only be -1, '0', or '1'.
  if (currChar != '0' && currChar != '1')
    return ERR_BRIGHTNESS;

  // Bit was received.

  // This bit is the first bit received.
  if (lastChar == -1) {
    if (currChar == '0')
      return BRIGHTNESS_OFF;
    else
      return BRIGHTNESS_ON;
  }

  // This bit is not the first bit received.
  if (currChar == lastChar)
    return BRIGHTNESS_OFF;
  else
    return BRIGHTNESS_ON;
}

int ruanEncoding(char currBit, char lastBit/*, bool & repBrightnessFlag*/) {
  // No data has yet been received.
  if (currBit == -1)
    return NO_DATA_BRIGHTNESS;

  // Error. The character should only be -1, '0', or '1'.
  if (currBit != '0' && currBit != '1')
    return ERR_BRIGHTNESS;

  // Bit was received.

  // No repetition. This is the same as a noEncoding scheme.
  if (currBit != lastBit) {
    repBrightnessFlag = true;
    return noEncoding(currBit);
  }

  // Repetition. Alternate between the noEncoding brightness and a specified repeat brightness.
  int brightness = ERR_BRIGHTNESS;
  if (repBrightnessFlag)
    brightness = BRIGHTNESS_REP;
  else
    brightness = noEncoding(currBit);

  repBrightnessFlag = !repBrightnessFlag;
  return brightness;
}

// the loop routine runs over and over again forever:
void loop() {
  if (Serial.available() > 0) {
    byteRead = Serial.read();
    // analogWrite(led, noEncoding(byteRead));
 
    // analogWrite(led, nrziEncoding(byteRead, lastByteRead));
     analogWrite(led, ruanEncoding(byteRead, lastByteRead/*, repBrightnessFlag*/));

    lastByteRead = byteRead;
  }
  else {
    analogWrite(led, 0);
  }
    

  // set the brightness of pin 9:
  

  // wait for 30 milliseconds to see the dimming effect
  delay(1000);
}
