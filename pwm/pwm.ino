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

int led = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

bool flag = true;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  if (flag)
    brightness = BRIGHTNESS_ON;
  else
    brightness = BRIGHTNESS_OFF;
  flag = !flag;
  
  // set the brightness of pin 9:
  analogWrite(led, brightness);

  // wait for 30 milliseconds to see the dimming effect
  delay(1000);
}
