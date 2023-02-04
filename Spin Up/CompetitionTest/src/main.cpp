/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// SpinnerMotor         motor         18              
// Drivetrain           drivetrain    1, 10, 11, 20   
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  Drivetrain.setDriveVelocity(30, percent);
  SpinnerMotor.setVelocity(100, percent);
  Drivetrain.driveFor(145, inches, false);
  SpinnerMotor.spinFor(forward, 10000, degrees, false);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
motor leftMotorA = motor(PORT1, ratio18_1, false);
motor leftMotorB = motor(PORT10, ratio18_1, false);
motor leftMotorC = motor(PORT2, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
motor rightMotorA = motor(PORT11, ratio18_1, true);
motor rightMotorB = motor(PORT20, ratio18_1, true);
motor rightMotorC = motor(PORT12, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);
motor SpinnerMotor = motor(PORT18, ratio18_1, false);
controller Controller1 = controller(primary);
float slowSpeedPercentage = .5F;
int slowestSpeedPercentage = 10;

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1RightShoulderControlMotorsStopped = true;
bool DrivetrainNeedsToBeStopped_Controller1 = true;
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    if(true) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis4
      // right = Axis3 - Axis4
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis4.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis4.position();

      // check if the values are inside of the deadband range
      if (abs(drivetrainLeftSideSpeed) < 5 && abs(drivetrainRightSideSpeed) < 5) {
        // check if the motors have already been stopped
        if (DrivetrainNeedsToBeStopped_Controller1) {
          // stop the drive motors
          LeftDriveSmart.stop();
          RightDriveSmart.stop();
          // tell the code that the motors have been stopped
          DrivetrainNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the motors next time the input is in the deadband range
        DrivetrainNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainNeedsToBeStopped_Controller1) {
        if (Controller1.ButtonA.pressing())
        {
          LeftDriveSmart.setVelocity((drivetrainLeftSideSpeed * slowSpeedPercentage), percent);
        }
        else
        {
          LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        }
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainNeedsToBeStopped_Controller1) {
        if (Controller1.ButtonA.pressing())
        {
          RightDriveSmart.setVelocity((drivetrainRightSideSpeed * slowSpeedPercentage), percent);
        }
        else
        {
          RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        }
        RightDriveSmart.spin(forward);
      }
      // check the ButtonR1/ButtonR2 status to control SpinnerMotor
      if (Controller1.ButtonR1.pressing()) {
        if(Controller1.ButtonA.pressing()) {
          SpinnerMotor.setVelocity(50, percent);
        }
        else 
        {
          SpinnerMotor.setVelocity(100, percent);
        }
        SpinnerMotor.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        if(Controller1.ButtonA.pressing()) {
          SpinnerMotor.setVelocity(50, percent);
        }
        else 
        {
          SpinnerMotor.setVelocity(100, percent);
        }
        SpinnerMotor.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        SpinnerMotor.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
      if (Controller1.ButtonUp.pressing()) {
        LeftDriveSmart.setVelocity(slowestSpeedPercentage, percent);
        LeftDriveSmart.spin(forward);
        RightDriveSmart.setVelocity(slowestSpeedPercentage, percent);
        RightDriveSmart.spin(forward);
      }
      else if (Controller1.ButtonDown.pressing()) {
        LeftDriveSmart.setVelocity(slowestSpeedPercentage, percent);
        LeftDriveSmart.spin(reverse);
        RightDriveSmart.setVelocity(slowestSpeedPercentage, percent);
        RightDriveSmart.spin(reverse);
      }
      else if (Controller1.ButtonLeft.pressing()) {
        LeftDriveSmart.setVelocity(slowestSpeedPercentage, percent);
        LeftDriveSmart.spin(reverse);
        RightDriveSmart.setVelocity(slowestSpeedPercentage, percent);
        RightDriveSmart.spin(forward);
      }
      else if (Controller1.ButtonRight.pressing()) {
        LeftDriveSmart.setVelocity(slowestSpeedPercentage, percent);
        LeftDriveSmart.spin(forward);
        RightDriveSmart.setVelocity(slowestSpeedPercentage, percent);
        RightDriveSmart.spin(reverse);
      }
      else if (abs(drivetrainLeftSideSpeed) < 5 && abs(drivetrainRightSideSpeed) < 5 && !Controller1.ButtonRight.pressing() && !Controller1.ButtonLeft.pressing() && !Controller1.ButtonUp.pressing() && !Controller1.ButtonDown.pressing())
      {
        LeftDriveSmart.stop();
        RightDriveSmart.stop();
      }
    }
    wait(20, msec); 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
