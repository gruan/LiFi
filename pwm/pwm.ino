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

int BRIGHTNESS_ON = 100;
int BRIGHTNESS_OFF = 50;
int ERR_BRIGHTNESS = 5;
int NO_DATA_BRIGHTNESS = 0;

int led = 9;           // the PWM pin the LED is attached to

int byteRead = -1;
int lastByteRead = -1;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(1);
}

int determineBrightness(char currChar, char lastChar) {
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

// the loop routine runs over and over again forever:
void loop() {
  if (Serial.available() > 0)
    byteRead = Serial.read();

  // set the brightness of pin 9:
  analogWrite(led, determineBrightness(byteRead, lastByteRead));
  lastByteRead = byteRead;

  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
