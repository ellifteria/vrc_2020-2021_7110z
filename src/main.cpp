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
  // Create GUI
  Brain.Screen.printAt(30, 120, ((std::string)"[+] Preparing UI").c_str());
  
  
  // AUTON DECLARATION
  Settings.addAuton(3121, "3121; Skills");
  
  // SCREEN DECLARATION
  ZUI_Screen myScreen = ZUI_Screen();

  // GRID CAPTIONS DECLARATION
  ZUI_Text r1 = ZUI_Text("1", 130, 50);
  ZUI_Text r2 = ZUI_Text("2", 130, 80);
  ZUI_Text r3 = ZUI_Text("3", 130, 110);
  ZUI_Text r4 = ZUI_Text("4", 130, 140);
  ZUI_Text r5 = ZUI_Text("5", 130, 170);
  ZUI_Text r6 = ZUI_Text("6", 130, 200);

  // SELECTION SCREEN TILES DECLARATION
  ZUI_GameTile gt121 = ZUI_GameTile(90, 30, 30, 30, "grey");
  ZUI_GameTile gt122 = ZUI_GameTile(90, 60, 30, 30, "grey");
  ZUI_GameTile gt123 = ZUI_GameTile(90, 90, 30, 30, "grey");
  ZUI_GameTile gt124 = ZUI_GameTile(90, 120, 30, 30, "grey");
  ZUI_GameTile gt125 = ZUI_GameTile(90, 150, 30, 30, "grey");
  ZUI_GameTile gt126 = ZUI_GameTile(90, 180, 30, 30, "grey");

  // ALLIANCE SELECTION SCREEN TILES DECLARATION
  ZUI_GameTile gt0231 = ZUI_GameTile(120, 30, 30, 30, "grey");
  ZUI_GameTile gt0221 = ZUI_GameTile(150, 30, 30, 30, "grey");
  ZUI_GameTile gt0211 = ZUI_GameTile(180, 30, 30, 30, "grey");
  ZUI_GameTile gt0232 = ZUI_GameTile(120, 60, 30, 30, "grey");
  ZUI_GameTile gt0222 = ZUI_GameTile(150, 60, 30, 30, "grey");
  ZUI_GameTile gt0212 = ZUI_GameTile(180, 60, 30, 30, "grey");
  ZUI_GameTile gt0233 = ZUI_GameTile(120, 90, 30, 30, "grey");
  ZUI_GameTile gt0223 = ZUI_GameTile(150, 90, 30, 30, "grey");
  ZUI_GameTile gt0213 = ZUI_GameTile(180, 90, 30, 30, "grey");
  ZUI_GameTile gt0234 = ZUI_GameTile(120, 120, 30, 30, "grey");
  ZUI_GameTile gt0224 = ZUI_GameTile(150, 120, 30, 30, "grey");
  ZUI_GameTile gt0214 = ZUI_GameTile(180, 120, 30, 30, "grey");
  ZUI_GameTile gt0235 = ZUI_GameTile(120, 150, 30, 30, "grey");
  ZUI_GameTile gt0225 = ZUI_GameTile(150, 150, 30, 30, "grey");
  ZUI_GameTile gt0215 = ZUI_GameTile(180, 150, 30, 30, "grey");
  ZUI_GameTile gt0236 = ZUI_GameTile(120, 180, 30, 30, "grey");
  ZUI_GameTile gt0226 = ZUI_GameTile(150, 180, 30, 30, "grey");
  ZUI_GameTile gt0216 = ZUI_GameTile(180, 180, 30, 30, "grey");
  ZUI_GameTile gt0111 = ZUI_GameTile(30, 30, 30, 30, "grey");
  ZUI_GameTile gt0121 = ZUI_GameTile(60, 30, 30, 30, "grey");
  ZUI_GameTile gt0131 = ZUI_GameTile(90, 30, 30, 30, "grey");
  ZUI_GameTile gt0112 = ZUI_GameTile(30, 60, 30, 30, "grey");
  ZUI_GameTile gt0122 = ZUI_GameTile(60, 60, 30, 30, "grey");
  ZUI_GameTile gt0132 = ZUI_GameTile(90, 60, 30, 30, "grey");
  ZUI_GameTile gt0113 = ZUI_GameTile(30, 90, 30, 30, "grey");
  ZUI_GameTile gt0123 = ZUI_GameTile(60, 90, 30, 30, "grey");
  ZUI_GameTile gt0133 = ZUI_GameTile(90, 90, 30, 30, "grey");
  ZUI_GameTile gt0114 = ZUI_GameTile(30, 120, 30, 30, "grey");
  ZUI_GameTile gt0124 = ZUI_GameTile(60, 120, 30, 30, "grey");
  ZUI_GameTile gt0134 = ZUI_GameTile(90, 120, 30, 30, "grey");
  ZUI_GameTile gt0115 = ZUI_GameTile(30, 150, 30, 30, "grey");
  ZUI_GameTile gt0125 = ZUI_GameTile(60, 150, 30, 30, "grey");
  ZUI_GameTile gt0135 = ZUI_GameTile(90, 150, 30, 30, "grey");
  ZUI_GameTile gt0116 = ZUI_GameTile(30, 180, 30, 30, "grey");
  ZUI_GameTile gt0126 = ZUI_GameTile(60, 180, 30, 30, "grey");
  ZUI_GameTile gt0136 = ZUI_GameTile(90, 180, 30, 30, "grey");

 // SELECTED BLUE SELECTION SCREEN TILES DECLARATION
  ZUI_GameTile gt21s = ZUI_GameTile(90, 30, 30, 30, "blue");
  ZUI_GameTile gt22s = ZUI_GameTile(90, 60, 30, 30, "blue");
  ZUI_GameTile gt23s = ZUI_GameTile(90, 90, 30, 30, "blue");
  ZUI_GameTile gt24s = ZUI_GameTile(90, 120, 30, 30, "blue");
  ZUI_GameTile gt25s = ZUI_GameTile(90, 150, 30, 30, "blue");
  ZUI_GameTile gt26s = ZUI_GameTile(90, 180, 30, 30, "blue");

 // SELECTED RED SELECTION SCREEN TILES DECLARATION
  ZUI_GameTile gt11s = ZUI_GameTile(90, 30, 30, 30, "red");
  ZUI_GameTile gt12s = ZUI_GameTile(90, 60, 30, 30, "red");
  ZUI_GameTile gt13s = ZUI_GameTile(90, 90, 30, 30, "red");
  ZUI_GameTile gt14s = ZUI_GameTile(90, 120, 30, 30, "red");
  ZUI_GameTile gt15s = ZUI_GameTile(90, 150, 30, 30, "red");
  ZUI_GameTile gt16s = ZUI_GameTile(90, 180, 30, 30, "red");

  // SELECTED GREEN SELECTION SCREEN TILES DECLARATION
  ZUI_GameTile gt311s = ZUI_GameTile(90, 30, 30, 30, "green");
  ZUI_GameTile gt312s = ZUI_GameTile(90, 60, 30, 30, "green");
  ZUI_GameTile gt313s = ZUI_GameTile(90, 90, 30, 30, "green");
  ZUI_GameTile gt314s = ZUI_GameTile(90, 120, 30, 30, "green");
  ZUI_GameTile gt315s = ZUI_GameTile(90, 150, 30, 30, "green");
  ZUI_GameTile gt316s = ZUI_GameTile(90, 180, 30, 30, "green");

  // PAGES DECLARATION
  ZUI_Page p0 = ZUI_Page();
  ZUI_Page p1 = ZUI_Page();
  ZUI_Page p2 = ZUI_Page();
  ZUI_Page p3121 = ZUI_Page();

  
  // BUTTON DECLARATIONS
  ZUI_Button backp0 = ZUI_Button(420, 30, 30, 30, greyColor, "<", "page=0");
  ZUI_Button backp1 = ZUI_Button(420, 30, 30, 30, greyColor, "<", "page=1");
  ZUI_Button backp2 = ZUI_Button(420, 30, 30, 30, greyColor, "<", "page=2");

  // PAGE: p0 - Alliance Selection Screen

  // p0: Title
  ZUI_Text p0title = ZUI_Text("Choose alliance", 270, 60);
  p0.add(p0title);

  // p0: Tiles
  p0.add(gt0111);
  p0.add(gt0121);
  p0.add(gt0131);
  p0.add(gt0112);
  p0.add(gt0122);
  p0.add(gt0132);
  p0.add(gt0113);
  p0.add(gt0123);
  p0.add(gt0133);
  p0.add(gt0114);
  p0.add(gt0124);
  p0.add(gt0134);
  p0.add(gt0115);
  p0.add(gt0125);
  p0.add(gt0135);
  p0.add(gt0116);
  p0.add(gt0126);
  p0.add(gt0136);
  p0.add(gt0211);
  p0.add(gt0221);
  p0.add(gt0231);
  p0.add(gt0212);
  p0.add(gt0222);
  p0.add(gt0232);
  p0.add(gt0213);
  p0.add(gt0223);
  p0.add(gt0233);
  p0.add(gt0214);
  p0.add(gt0224);
  p0.add(gt0234);
  p0.add(gt0215);
  p0.add(gt0225);
  p0.add(gt0235);
  p0.add(gt0216);
  p0.add(gt0226);
  p0.add(gt0236);
  
  // p0: Buttons
  p0.add(ZUI_Button(285, 75, 60, 30, redColor, "1", "page=1"));
  p0.add(ZUI_Button(375, 75, 60, 30, blueColor, "2", "page=2"));
  p0.add(ZUI_Button(330, 125, 60, 30, greenColor, "3", "page=3121"));
  
  // PAGE: p1 - Red Alliance Screen

  // p1: Title
  ZUI_Text p1title = ZUI_Text("Choose auton", 270, 60);
  p1.add(p1title);

  // p1: Tiles
  p1.add(gt121);
  p1.add(gt122);
  p1.add(gt123);
  p1.add(gt124);
  p1.add(gt125);
  p1.add(gt126);

  // p1: Grid
  p1.add(r1);
  p1.add(r2);
  p1.add(r3);
  p1.add(r4);
  p1.add(r5);
  p1.add(r6);

  // p1: Buttons
  p1.add(backp0);

  // PAGE: p2 - Blue Alliance Screen

  // p2: Title
  ZUI_Text p2title = ZUI_Text("Choose auton", 270, 60);
  p2.add(p2title);

  // p2: Tiles
  p2.add(gt121);
  p2.add(gt122);
  p2.add(gt123);
  p2.add(gt124);
  p2.add(gt125);
  p2.add(gt126);

  //p2: Grid
  p2.add(r1);
  p2.add(r2);
  p2.add(r3);
  p2.add(r4);
  p2.add(r5);
  p2.add(r6);

  // p2: Buttons
  p2.add(backp0);

  // PAGE: p3121 - Skills Selection Screen

  // p3121: Title
  ZUI_Text p121title = ZUI_Text("Auton " + Settings.parseAuton(3121, 0), 270, 60);
  p3121.add(p121title);
  ZUI_Text p121text = ZUI_Text(Settings.parseAuton(3121, 1), 270, 90);
  p3121.add(p121text);

  // p3121: Tiles
  p3121.add(gt121);
  p3121.add(gt312s);
  p3121.add(gt123);
  p3121.add(gt124);
  p3121.add(gt125);
  p3121.add(gt126);

  // p3121: Grid
  p3121.add(r1);
  p3121.add(r2);
  p3121.add(r3);
  p3121.add(r4);
  p3121.add(r5);
  p3121.add(r6);

  // p3121: Buttons
  p3121.add(ZUI_Button(285, 180, 90, 30, greenColor, "Confirm", "auton=3121;finalpage=true"));
  p3121.add(backp0);


  // ADD PAGES TO SCREEN
  myScreen.addPage(0, p0);
  myScreen.addPage(1, p1);
  myScreen.addPage(2, p2);
  myScreen.addPage(3121, p3121);

  // RUN UI
  Brain.Screen.printAt(30, 150, ((std::string)"[+] Running UI").c_str());
  myScreen.handleUI();
}


void autonomous( void ) {
  releaseFlap();

  // Calibrate Gyroscope
  Inert.startCalibration();
  Brain.Screen.clearScreen();
  while(Inert.isCalibrating())
  {
    Brain.Screen.printAt(30, 30, ((std::string)"[.] Callibrating Gyroscope").c_str());
    wait(500, msec);
  }
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(30, 60, ((std::string)"[+] Gyroscope Calibrated").c_str());

  // Run autonomous program
  runAuton();
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