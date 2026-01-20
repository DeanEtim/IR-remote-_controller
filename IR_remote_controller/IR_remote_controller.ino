#include <Servo.h>
#include <Arduino.h>

#if !defined(STR_HELPER)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif
 
#include <IRremote.hpp>  // include the library

// Remote
#define IR_RECEIVE_PIN 2

// Servo
Servo myServo;
int servoAngle = 0;

//xternal device to be controlled
int device = 12;
int prompt = 0;

void setup(void) {
  // Initialize Serial communication
  Serial.begin(115200);

  // Initialize receiver
  IrReceiver.begin(IR_RECEIVE_PIN);

  Serial.print("Ready to receive IR signals at pin: ");
  Serial.println(IR_RECEIVE_PIN);

  // initialize servomotor
  myServo.attach(9);
  myServo.write(0);

  // declare device pins
  pinMode(device, OUTPUT);
  pinMode(13, OUTPUT);
}  // end setup

void loop(void) {
  IrReceiver.resume();
  if (IrReceiver.decode()) {
    int command = IrReceiver.decodedIRData.command;
    switch (command) {
      case 0x72:
        blinkOnce();
        Serial.println(command, HEX);
        break;
      case 0x71:
        blinkTwice();
        Serial.println(command, HEX);
        break;
      case 0x63:
        blinkThrice();
        Serial.println(command, HEX);
      case 0x61:
        blinkFourTimes();
        Serial.println(command, HEX);
        break;
      case 0x8:
        Serial.println(command, HEX);
        prompt += 1;
        if (prompt == 1) {
          digitalWrite(device, HIGH);
          Serial.println("Hello world!");
          delay(100);
        } else if (prompt == 2) {
          digitalWrite(device, LOW);
          Serial.println("Your Device has been successfully turned off");
          delay(100);
          prompt = 0;
        }
        break;
    }  // end switch_case
  }    // end if
}  // end main loop

void blinkOnce(void) {
  digitalWrite(device, 1);
  delay(500);
  digitalWrite(device, 0);
}  // end bliknOnce

void blinkTwice(void) {
  for (int i = 1; i <= 2; i++) {
    digitalWrite(device, 1);
    delay(500);
    digitalWrite(device, 0);
    delay(300);
  }  //end blinkFourTimes
}  // end blinkTwice

void blinkThrice(void) {
  for (int i = 1; i <= 3; i++) {
    digitalWrite(device, 1);
    delay(500);
    digitalWrite(device, 0);
    delay(300);
  }  //end blinkFourTimes
}  // end blinkThrice

void blinkFourTimes(void) {
  for (int i = 1; i <= 4; i++) {
    digitalWrite(device, 1);
    delay(500);
    digitalWrite(device, 0);
    delay(300);
  }  //end blinkFourTimes
}  // end blinkFourTime