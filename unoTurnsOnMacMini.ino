//#define DEBUG // Enable this to disable normal job activities (see main func).

#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#define __Arduino_UNO
#define angleToPressThePowerButton 90 // Different values for Arduino UNO and Attiny85 since Servo.h controls the servo slightly different.
#define increasingStepsForServoControl 1 // This stepping value should be multiple of angleToPressThePowerButton
#define delayAmongEachServoAngleUpdating_ms 15
#define servoPin 9
#include <Servo.h>
Servo servo;

// Default definitions are for Attiny85 boards
// This board offers less capabilities/features.
#else
#define __Attiny_85
#define angleToPressThePowerButton 90 // Different values for Arduino UNO and Attiny85 since Adafruit_SoftServo.h controls the servo slightly different.
#define increasingStepsForServoControl 1 // This stepping value should be multiple of angleToPressThePowerButton
#define delayAmongEachServoAngleUpdating_ms 15
uint8_t servoPin = 0;
#include <Adafruit_SoftServo.h>
Adafruit_SoftServo servo;
#endif

//Same delay for button pressing no matter the microcontroller. 
#define buttonPressedDelay_ms 250

void servoMovement (int initialAngle, int limitAngle, int steps)
{
#ifdef __Arduino_UNO
  Serial.print("servoMovement from ");
  Serial.print(initialAngle);
  Serial.print(" to ");
  Serial.print(limitAngle);
  Serial.print(", steping: ");
  Serial.println(steps);
#endif
  for (int i = initialAngle; i != limitAngle + steps ; i = i + steps)
  {
    servo.write(i);
    delay(delayAmongEachServoAngleUpdating_ms); // Waiting for the servomotor to reach the angle.
#ifdef __Attiny_85
    servo.refresh(); // Needed by the Adafruit_SoftServo library
#elif defined(__Arduino_UNO)
    Serial.print("Servomotor's angle: ");
    Serial.println(i);
#endif
  }
}

void bidirectionalServoMovement(int limitAngle, int steps)
{
#ifdef __Arduino_UNO
  Serial.print("Bidirectional Servo Movement from 0 to ");
  Serial.println(limitAngle);
#endif
  servoMovement(0, limitAngle, steps);
  delay(buttonPressedDelay_ms);
  servoMovement(limitAngle, 0, steps * -1);
}

void bootAnimation()
{
#ifdef __Arduino_UNO
  Serial.println("Boot Animation");
#endif
  bidirectionalServoMovement(50, 10); delay(500);
  bidirectionalServoMovement(75, 5); delay(500);
}

void mainJob()
{
  bootAnimation();
  bidirectionalServoMovement(angleToPressThePowerButton, increasingStepsForServoControl);
}

void setup()
{
  servo.attach(servoPin);
  servo.write(0);
#ifdef __Arduino_UNO
  Serial.begin(115200);
  Serial.println("Running on ATMEGA328");
#ifdef DEBUG
  Serial.println("Running on DEBUG mode");
#endif
#else
  servo.refresh(); // Needed by the Adafruit_SoftServo library
#endif

  // TODO: Investigate why when this chunk of code is moved to the loop func, the serialEvent interruption
  // stops working, however moving this code to the setup function makes sense since this is only needed once
  // at the startup.
#ifndef DEBUG
  mainJob();
#endif
}

#ifdef __Arduino_UNO
void serialEvent()
{
  Serial.println("Serial interruption detected");
  String data;
  while (Serial.available())
  {
    data = Serial.readStringUntil('\n');
    Serial.print("Starting test from 0 to ");
    Serial.println(data);
    bidirectionalServoMovement(data.toInt(), 1);
  }
}
#endif

void loop()
{
  delay(1); //Decrease the CPU consumption.
}
