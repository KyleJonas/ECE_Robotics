// Runs two motors simultaneously.
// Author: Dominic Celiano, C3C
// Date: 10/21/2014

// Requires the Adafruit_Motorshield v2 library 
//   https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
// And AccelStepper with AFMotor support 
//   https://github.com/adafruit/AccelStepper

#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

//The indented lines below are initializing the stepper motors, named stepper1 and stepper2.

  // Create the motor shield object with the default I2C address
  Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
  // Or, create it with a different I2C address (say for stacking)
  // Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 


  // Connect a stepper motor with 360/7.5 steps per revolution (a 7.5 degree stepper motor)
  // to motor port #2 (M3 and M4)
  Adafruit_StepperMotor *leftMotor = AFMS.getStepper(360/7.5, 1);
  Adafruit_StepperMotor *rightMotor = AFMS.getStepper(360/7.5, 2);
  
  
  // Functions to define what a step is for each motor. These values can be changed to DOUBLE or INTERLEAVE or MICROSTEP.
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
  
  
  //Initialize each stepper with its functions to step.
  AccelStepper stepper1(left_forwardstep, left_backwardstep);
  AccelStepper stepper2(right_forwardstep, right_backwardstep); 


  //input revoultions(for stepper1 and stepper2) and RPMs below:
  //for negative rotation, enter a negative revolution
  int steps1 = 99999999; // the number of revolutions we want the motors to make (how far we want it to go)
  int steps2 = 99999999;
  int RPM1 = 100; // The speed in steps per second //48 = One revolution of the wheel per second
  int RPM2 = 100;


void setup()
{  
  AFMS.begin(); // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  
  //stepper1.setMaxSpeed(500); //maybe remove
  //stepper2.setMaxSpeed(500);

  stepper1.setAcceleration(200.0);
  stepper2.setAcceleration(200.0);
  stepper1.setMaxSpeed(RPM1);
  stepper2.setMaxSpeed(RPM2);  
  	
}

void loop()
{  
    stepper1.moveTo(steps1);
    stepper2.moveTo(steps2);  
    stepper1.run();
    stepper2.run();
    steps1 = steps1 + 9999999;
    steps2 = steps2 + 9999999;
}



////////////////////////
//////FUNCTION//////////
////DECLARATIONS////////
///////BELOW////////////
////////////////////////

