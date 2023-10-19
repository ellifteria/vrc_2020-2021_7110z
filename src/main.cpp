/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|CONTROLS:                                       |
|                                                |
|W.P. = While Pressed                            |
|                                                |
|X Button: Speed Control Button 1                |
|A Button: Tray Bypass Button FWD                |
|B Button: Speed Control Button 2                |
|Y Button: Tray Bypass Button REV                |
|A Button and Y Button: Reset Rotation           |
|                                                |
|Up Button: WP ARM UP                            |
|Down Button: WP ARM DOWN                        |
|                                                |
|Left Button: Speed Control Button 1             |
|Right Button: Speed Control Button 2            |
|                                                |
|R1: WP Upper in                                 |
|R2: WP Upper out                                |
|                                                |
|L1: WP Intake & lower in                        |
|L2: WP Intake & lower out                       |
|                                                |
|                                                |
|Arcade Rotate_on_Right:                         |!CURRENT DRIVE METHOD!
|Left Joystick U/D(Ch3): For/Back                |
|Left Joystick R/L(Ch4): N/A                     |!Free!
|Right Joystick U/D(Ch2): N/A                    |!Free!
|Right Joystick R/L(Ch1): Rotate                 |
|                                                |
|Arcade Rotate_on_Left:                          |!UNUSED DRIVE METHOD!
|Left Joystick U/D(Ch3): N/A                     |!Free!
|Left Joystick R/L(Ch4): Rotate                  |
|Right Joystick U/D(Ch2): For/Back               |
|Right Joystick R/L(Ch1): N/A                    |!Free!
|                                                |
|                                                |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

/*
Tiles are named by three digit codes

Digit 1: Alliance (or skills)
  1: Red
  2: Blue
  3: Skills (Digits 2 & 3 are from perspective of Red)

Digit 2: Row
  1: Home row
  2: 1 past home row
  3: 2 past home row
  etc.

Digit 3: Column
  1: Farthest left
  2: Second farthest left
  etc.

Autonomous programs have a fourth digit indicating which program it is
  (Digit is 1 unless tiles have multiple programs)
*/


#include "functions.h"

using namespace std;
using namespace vex;
// A global instance of vex::competition
vex::competition Competition;

void runAuton(int auton) //Runs autonomous prgram stored in Settings and selected by UI
{
  switch(auton)
  {
    case 3121: //Skills autonomous
    {
      /*
      ROW #1
      */

      //Tower #1
      intakesOn();
      moveForward(1.175, movementUnits::fieldTiles, autonSpeed);
      // GyroTurnLeft(125);
      TurnLeftToHeading(-125);
      intakesOff();
      moveForward(1.185, movementUnits::fieldTiles, autonSpeed);
      launchBall();

      //Tower #2
      moveBackward(.5, movementUnits::fieldTiles, autonSpeed);
      // GyroTurnRight(125.0);
      TurnRightToHeading(0);
      intakesOn();
      moveForward(2.2, movementUnits::fieldTiles, autonSpeed);
      // GyroTurnLeft(87.5);
      TurnLeftToHeading(-90);
      moveForward(.2, movementUnits::fieldTiles, autonSpeed);
      intakesOff();
      launchBall();
      wait(10,msec);
      launchBall();
      wait(10,msec);
      launchBall();
      intakesOut(1);
      intakeBall(1);
      
      //Tower #3
      moveBackward(1, movementUnits::fieldTiles, autonSpeed);
      // GyroTurnRight(85);
      TurnRightToHeading(90);
      intakesOut(50);
      intakesOn();
      smartDriveTime(vex::directionType::fwd, 2.50, movementUnits::fieldTiles, autonSpeed);
      moveBackward(1.1, movementUnits::fieldTiles, autonSpeed);
      // GyroTurnLeft(40.5);
      TurnLeftToHeading(-40);
      moveForward(1.3, movementUnits::fieldTiles, autonSpeed);
      intakesOff();
      launchBall();

      /*
      ROW #2
      */
      
      //Tower #4
      moveBackward(1.65, movementUnits::fieldTiles, autonSpeed);
      // GyroTurnLeft(30.5);
      TurnRightToHeading(0);
      intakesOn();
      smartDriveTime(vex::directionType::fwd, 1.45, movementUnits::fieldTiles, autonSpeed);
      moveBackward(2.6, movementUnits::fieldTiles, autonSpeed);
      // GyroTurnRight(86.5);
      TurnRightToHeading(90);
      moveForward(.55, movementUnits::fieldTiles, autonSpeed);
      intakesOff();
      launchBall();
      wait(10,msec);
      launchBall();
      wait(10,msec);
      launchBall();

      //Tower #5
      moveBackward(.85, movementUnits::fieldTiles, autonSpeed);
      // GyroTurnRight(82);
      TurnRightToHeading(180);
      intakesOn();
      // moveForward(2.59, movementUnits::fieldTiles, autonSpeed);
      smartDriveTime(vex::directionType::fwd, 2.61, movementUnits::fieldTiles, autonSpeed);
      moveBackward(.95, movementUnits::fieldTiles, autonSpeed);
      // GyroTurnLeft(45);
      TurnLeftToHeading(135);
      moveForward(1.2, movementUnits::fieldTiles, autonSpeed);
      intakesOff();
      launchBall();
      moveBackward(.5, movementUnits::fieldTiles, autonSpeed);
      
      break;
    }
    default:
    {
      break;
    }
  }
}


void pre_auton( void ) {
  vexcodeInit();
}


void autonomous( void ) {
  releaseFlap();

  //Calibrate Gyroscope
  Inert.startCalibration();
  Brain.Screen.clearScreen();
  while(Inert.isCalibrating())
  {
    Brain.Screen.printAt(30, 30, ((std::string)"[.] Callibrating Gyroscope").c_str());
    wait(500, msec);
  }
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(30, 60, ((std::string)"[+] Gyroscope Calibrated").c_str());

  //Run autonomous program
  runAuton(Settings.getAuton());
}

void usercontrol( void ) {
  while (1) {

    checkMotorTemp(RollerU, Controller);
    checkMotorTemp(RollerL, Controller);

    //Chasis code
    
    LFM_SPEED.setTo(Controller.Axis3.position(pct) + Controller.Axis1.position(pct));
    RFM_SPEED.setTo(Controller.Axis3.position(pct) - Controller.Axis1.position(pct));
    LBM_SPEED.setTo(LFM_SPEED.asPercent());
    RBM_SPEED.setTo(RFM_SPEED.asPercent());
    if(Controller.ButtonX.pressing() || Controller.ButtonLeft.pressing())
    {
      LFM_SPEED.divide(2);
      RFM_SPEED.divide(2);
      LBM_SPEED.divide(2);
      RBM_SPEED.divide(2);
    }
    if (Controller.ButtonB.pressing() || Controller.ButtonRight.pressing()) 
    {
      LFM_SPEED.divide(3);
      RFM_SPEED.divide(3);
      LBM_SPEED.divide(3);
      RBM_SPEED.divide(3);
    }
    LFM.spin(directionType::fwd,LFM_SPEED.asPercent(), velocityUnits::pct);
    RFM.spin(directionType::fwd,RFM_SPEED.asPercent(), velocityUnits::pct);
    LBM.spin(directionType::fwd,LBM_SPEED.asPercent(), velocityUnits::pct);
    RBM.spin(directionType::fwd,RBM_SPEED.asPercent(), velocityUnits::pct);

    //Intake Code
    if(Controller.ButtonL1.pressing())
    {
      IntakeL.spin(directionType::fwd, INTAKE_SPEED.asPercent(), velocityUnits::pct);
      IntakeR.spin(directionType::fwd, INTAKE_SPEED.asPercent(), velocityUnits::pct);
      RollerL.spin(directionType::fwd, ROLLERL_SPEED.asPercent(), velocityUnits::pct);
    }

    else if(Controller.ButtonL2.pressing())
    {
      IntakeL.spin(directionType::rev, INTAKE_SPEED.asPercent(), velocityUnits::pct);
      IntakeR.spin(directionType::rev, INTAKE_SPEED.asPercent(), velocityUnits::pct);
      RollerL.spin(directionType::rev, ROLLERL_SPEED.asPercent(), velocityUnits::pct);
    }

    else
    {
      IntakeL.stop();
      IntakeR.stop();
      RollerL.stop();
    }

    //Expeller Code
    if(Controller.ButtonR1.pressing())
    {
      RollerU.spin(directionType::fwd, ROLLERU_SPEED.asPercent(), velocityUnits::pct);
      if(!Controller.ButtonL1.pressing() && !Controller.ButtonL2.pressing())
      {
        RollerL.spin(directionType::fwd, ROLLERL_SPEED_SLOW.asPercent(), velocityUnits::pct);
      }
      // launchBall();
    }

    else if (Controller.ButtonR2.pressing())
    {
      RollerU.spin(directionType::rev, ROLLERU_SPEED.asPercent(), velocityUnits::pct);
      // RollerU.stop();
    }

    else
    {
      RollerU.stop();
    }

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}


int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100); //Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}