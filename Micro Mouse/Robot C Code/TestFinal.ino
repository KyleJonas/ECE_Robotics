// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
// Requires the Adafruit_Motorshield v2 library 
//   https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
// And AccelStepper with AFMotor support 
//   https://github.com/adafruit/AccelStepper

// This tutorial is for Adafruit Motorshield v2 only!
// Will not work with v1 shields

#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *leftMotor = AFMS.getStepper(360/7.5, 1);
Adafruit_StepperMotor *rightMotor = AFMS.getStepper(360/7.5, 2);

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
void left_forwardstep() {  
  leftMotor->onestep(FORWARD, SINGLE);
}
void left_backwardstep() {  
  leftMotor->onestep(BACKWARD, SINGLE);
}
void right_forwardstep() {  
  rightMotor->onestep(FORWARD, SINGLE);
}
void right_backwardstep() {  
  rightMotor->onestep(BACKWARD, SINGLE);
}

AccelStepper stepper1(left_forwardstep, left_backwardstep); // use functions to step
AccelStepper stepper2(right_forwardstep, right_backwardstep);

void setup()
{  
  AFMS.begin(); // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  //input revoultions(for motor1 and motor2) and RPMs below:
  //for negative rotation enter a negative revolution
  int revs1 = 2;
  int revs2 = 2;
  int RPM1 = 60;
  int RPM2 = 60;
  
  stepper1.setMaxSpeed(500);
  stepper2.setMaxSpeed(500);

  stepper1.setAcceleration(200.0);
  stepper2.setAcceleration(200.0);
  
  stepper1.moveTo((revs1*200)-3);
  stepper1.setSpeed(RPM1 * 3.75); //maybe remove
  stepper2.moveTo((revs2*200)+3);
  stepper2.setSpeed(RPM2 * 3.75); //
  	
}

void loop()
{  
    // Change direction at the limits
    if (stepper1.distanceToGo() == 0)
	stepper1.moveTo(-stepper1.currentPosition());

    if (stepper2.distanceToGo() == 0)
	stepper2.moveTo(-stepper2.currentPosition());

    stepper1.run();
    stepper2.run();
}
