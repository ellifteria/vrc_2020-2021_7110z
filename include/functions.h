/*
File containing functions used in User Control and Autonomous periods
*/

// #include "ZUI.h"

#include <vector>
#include <string>
#include <map>

#include "vex.h"

using namespace std;
using namespace vex;

#include "robot-config.h"
#include <list>
#include <iostream>


//Constants
const double pi = 3.141592653589793;
const double diameter = 3.25;
const double circumference = pi * diameter;
const double fieldTileLength = 24;

//Enums

enum movementUnits//User defined data type for storing distance measurements
{
  degrees,
  inches,
  fieldTiles
};

/*
Conversion Functions
*/

/*
Format is [TYPE1]2[TYPE2]
Convert from [TYPE1] to [TYPE2]
*/

//Distance conversions
double INCHES2DEGREES(double inches)
{
  //convert from distance to degrees
  double degrees = (inches/circumference)*360;
  return degrees;
}

double FIELDTILES2DEGREES(double fieldTiles)
{
  double degrees = INCHES2DEGREES(fieldTiles * fieldTileLength);
  return degrees;
}

//Speed conversions
int PCT2DPS(int pct)
{
  return pct*12;
}

int DPS2PCT(int dps)
{
  return dps/12;
}

int DPS2RPM(int dps)
{
  return dps/5;
}

int RPM2DPS(int rpm)
{
  return rpm*5;
}

int RPM2PCT(int rpm)
{
  return DPS2PCT(RPM2DPS(rpm));
}

int PCT2RPM(int pct)
{
  return DPS2RPM(PCT2DPS(pct));
}

class Speed
{
  /*
  Class of speed objects
    Allows speeds to be stored and easily converted between PCT, RPM, and DPS
  */
  protected:
    int speedPCT;
    int speedDPS;
    int speedRPM;
    velocityUnits type;

  public:
    Speed(int inSpeed, vex::velocityUnits inType)
    {
      type = inType;
      setTo(inSpeed, type);
    }

    void setTo(int inSpeed)
    {
      setTo(inSpeed, type);
    }

    void setTo(int inSpeed, vex::velocityUnits inType)
    {
      if(inType == vex::velocityUnits::pct)
      {
        speedPCT = inSpeed;
        speedDPS = PCT2DPS(speedPCT);
        speedRPM = PCT2RPM(speedPCT);
      }
      else if(inType == vex::velocityUnits::dps)
      {
        speedDPS = inSpeed;
        speedPCT = DPS2PCT(speedDPS);
        speedRPM = DPS2RPM(speedDPS);
      }
      else if(inType ==  vex::velocityUnits::rpm)
      {
        speedRPM = inSpeed;
        speedDPS = RPM2DPS(speedRPM);
        speedPCT = RPM2PCT(speedRPM);
      }
    }

    void divide(int amount)
    {
      speedDPS = speedDPS/amount;
      speedPCT = speedPCT/amount;
      speedRPM = speedRPM/amount;
    }

    int asPercent()
    {
      return speedPCT;
    }

    int asDPS()
    {
      return speedDPS;
    }

    int asRPM()
    {
      return speedRPM;
    }

    int val()
    {
      if(type == velocityUnits::pct)
      {
        return asPercent();
      }
      else if(type == velocityUnits::dps)
      {
        return asDPS();
      }
      else
      {
        return asRPM();
      }
    }

    void changeType(velocityUnits inType)
    {
      type = inType;
    }

};

//Variables
Speed autonSpeed = Speed(65, velocityUnits::pct);

double gyroErrL = 7;
double gyroErrHL = 0;
double gyroErrR = 6;
double gyroErrHR = 0;

Speed LFM_SPEED = Speed(0, velocityUnits::pct);
Speed RFM_SPEED = Speed(0, velocityUnits::pct);
Speed LBM_SPEED = Speed(0, velocityUnits::pct);
Speed RBM_SPEED = Speed(0, velocityUnits::pct);
Speed ROLLERL_SPEED = Speed(100, velocityUnits::pct);
Speed ROLLERU_SPEED = Speed(100, velocityUnits::pct);
Speed INTAKE_SPEED = Speed(100, velocityUnits::pct);
Speed ROLLERL_SPEED_SLOW = Speed(25, velocityUnits::pct);

/*
Game Functions
*/

void checkMotorTemp(motor inMotor, controller inController)//Temp values from: https://www.vexforum.com/t/v5-motor-temp-in-percent/52433/4
{
  /*
  Method to rumble controller to indicate if motors overheat
  */
  double temp = inMotor.temperature(temperatureUnits::celsius);
  if(temp < 50.0);
  else if(temp < 52.5)
  {
    inController.rumble(" .");
  }
  else if(temp < 57.5)
  {
    inController.rumble(" -");
  }
  else if(temp < 62.5)
  {
    inController.rumble("..");
  }
  else if(temp < 67.5)
  {
    inController.rumble("-.");
  }
}

void lockFlap()
{
  RollerL.spinFor(directionType::fwd, 50, rotationUnits::deg, ROLLERL_SPEED_SLOW.asPercent(), velocityUnits::pct);
  RollerL.setBrake(brakeType::hold);
  RollerL.stop(brakeType::hold);
}

void releaseFlap()
{
  RollerL.spinFor(directionType::rev, 100, rotationUnits::deg, ROLLERL_SPEED_SLOW.asPercent(), velocityUnits::pct);
  RollerL.stop();
  RollerL.setBrake(brakeType::coast);
}

/*
Movement Functions
*/
void moveForward(double amount, movementUnits units, Speed speed)
{
  double degrees = amount;
  //Convert amount to proper units if necessary
  if(units == movementUnits::fieldTiles)
  {
    degrees = FIELDTILES2DEGREES(amount);
  }
  else if(units == movementUnits::inches)
  {
    degrees = INCHES2DEGREES(amount);
  }
  LFM.spinFor(directionType::fwd, degrees,rotationUnits::deg,speed.asDPS(),velocityUnits::dps,false);
  RFM.spinFor(directionType::fwd, degrees,rotationUnits::deg,speed.asDPS(),velocityUnits::dps,false);
  LBM.spinFor(directionType::fwd, degrees,rotationUnits::deg,speed.asDPS(),velocityUnits::dps,false);
  RBM.spinFor(directionType::fwd, degrees,rotationUnits::deg,speed.asDPS(),velocityUnits::dps,true);
}

void moveBackward(double amount, movementUnits units, Speed speed)
{
  double degrees = amount;
  //Convert amount to proper units if necessary
  if(units == movementUnits::fieldTiles)
  {
    degrees = FIELDTILES2DEGREES(amount);
  }
  else if(units == movementUnits::inches)
  {
    degrees = INCHES2DEGREES(amount);
  }
  LFM.spinFor(directionType::rev, degrees,rotationUnits::deg,speed.asDPS(),velocityUnits::dps,false);
  RFM.spinFor(directionType::rev, degrees,rotationUnits::deg,speed.asDPS(),velocityUnits::dps,false);
  LBM.spinFor(directionType::rev, degrees,rotationUnits::deg,speed.asDPS(),velocityUnits::dps,false);
  RBM.spinFor(directionType::rev, degrees,rotationUnits::deg,speed.asDPS(),velocityUnits::dps,true);
}

void stopDrive()
{
  LFM.stop();
  LBM.stop();
  RFM.stop();
  RBM.stop();
}

void stopDriveHold()
{
  LFM.stop(brakeType::hold);
  LBM.stop(brakeType::hold);
  RFM.stop(brakeType::hold);
  RBM.stop(brakeType::hold);
}

void unHoldDrive()
{
  LFM.setBrake(brakeType::brake);
  LBM.setBrake(brakeType::brake);
  RFM.setBrake(brakeType::brake);
  RBM.setBrake(brakeType::brake);
}

void smartDriveTime(vex::directionType dir, double amount, movementUnits units, Speed speed)
{
  /*
  Method to move the robot a specific distance with safeguard in place if robot becomes stuck
    Uses built-in V5 motor encoders and built-in clock
    Moves robot until distance traveled = desired distance
    Or until time expires
      Sets motors to move at indicated speed
      Checks if robot has reached goal
      Checks time since started moving
      If time > 150% expected time or if robot reached goal
        Stop moving
    To be used in areas where robot often gets stuck and freezes while trying to complete movement
  */
  double degreeGoal = amount;
  //Convert amount to proper units if necessary
  if(units == movementUnits::fieldTiles)
  {
    degreeGoal = FIELDTILES2DEGREES(amount);
  }
  else if(units == movementUnits::inches)
  {
    degreeGoal = INCHES2DEGREES(amount);
  }
  //Calculate expected time
  double expectedTime = degreeGoal/speed.asDPS();// Degrees * (1/(Degrees/Seconds)) = Seconds
  //Collect initial values
  double startTime = Brain.timer(timeUnits::sec);
  double timeElapsed = 0;
  int startDegree = LFM.rotation(rotationUnits::deg);
  int degreesElapsed = 0;
  //Begin movement
  RFM.spin(dir, speed.asDPS(), velocityUnits::dps);
  LFM.spin(dir, speed.asDPS(), velocityUnits::dps);
  RBM.spin(dir, speed.asDPS(), velocityUnits::dps);
  LBM.spin(dir, speed.asDPS(), velocityUnits::dps);
  //Check if time expires or goal reached
  if(dir == vex::directionType::fwd)
  {
    while((timeElapsed < expectedTime*1.5) && (degreesElapsed<=(degreeGoal)))
    {
      degreesElapsed = LFM.rotation(rotationUnits::deg) - startDegree;
      timeElapsed = Brain.timer(timeUnits::sec) - startTime;
    }
  }
  else{
    while((timeElapsed < expectedTime*1.5) && (degreesElapsed<=(degreeGoal)))
    {
      degreesElapsed = startDegree - LFM.rotation(rotationUnits::deg);
      timeElapsed = Brain.timer(timeUnits::sec) - startTime;
    }
  }
  stopDrive();
}

/*
Gyro Turning Functions
*/

void GyroTurnLeft(double goal, Speed speed)
{
  /*
  Method to turn the robot in the counterclockwise direction using inertial sensor a specific amount
    Uses inertial sensor to initial angle
    Begins turning counterclockwise at speed indicated
    Continuously checks current angle
    Stops turn when the difference between the current and initial angles equals the intended turn magnitude
      takes into account slight error
  */
  double startAngle = Inert.rotation(rotationUnits::deg);
  double gyroVal = Inert.rotation(rotationUnits::deg);
  while(gyroVal > (startAngle-goal+gyroErrL))
  {
    LFM.spin(directionType::rev, speed.asDPS(), velocityUnits::dps);
    RFM.spin(directionType::fwd, speed.asDPS(), velocityUnits::dps);
    LBM.spin(directionType::rev, speed.asDPS(), velocityUnits::dps);
    RBM.spin(directionType::fwd, speed.asDPS(), velocityUnits::dps);
    gyroVal = Inert.rotation(rotationUnits::deg);
  }
  stopDriveHold();
  unHoldDrive();
}

void GyroTurnLeft(double goal)//GyroTurnLeft at standard speed
{
  GyroTurnLeft(goal, autonSpeed);
}

void GyroTurnRight(double goal, Speed speed)
{
  /*
  Method to turn the robot in the clockwise direction using inertial sensor a specific amount
    Uses inertial sensor to initial angle
    Begins turning clockwise at speed indicated
    Continuously checks current angle
    Stops turn when the difference between the current and initial angles equals the intended turn magnitude
      takes into account slight error
  */
  double startAngle = Inert.rotation(rotationUnits::deg);
  double gyroVal = Inert.rotation(rotationUnits::deg);
  while(gyroVal < (startAngle+goal-gyroErrR))
  {
    LFM.spin(directionType::fwd, speed.asDPS(), velocityUnits::dps);
    RFM.spin(directionType::rev, speed.asDPS(), velocityUnits::dps);
    LBM.spin(directionType::fwd, speed.asDPS(), velocityUnits::dps);
    RBM.spin(directionType::rev, speed.asDPS(), velocityUnits::dps);
    gyroVal = Inert.rotation(rotationUnits::deg);
  }
  stopDriveHold();
  unHoldDrive();
}

void GyroTurnRight(double goal)//GyroTurnRight at standard speed
{
  GyroTurnRight(goal, autonSpeed);
}

void TurnLeftToHeading(double goal, Speed speed)
{
  /*
  Method to turn the robot in the counterclockwise direction using inertial sensor a specific amount
    Uses inertial sensor to initial angle
    Begins turning counterclockwise at speed indicated
    Continuously checks current angle
    Stops turn when the difference between the current and initial angles equals the intended turn magnitude
      takes into account slight error
  */
  double gyroVal = Inert.rotation(rotationUnits::deg);
  while(gyroVal > (goal+gyroErrHL))
  {
    LFM.spin(directionType::rev, speed.asDPS(), velocityUnits::dps);
    RFM.spin(directionType::fwd, speed.asDPS(), velocityUnits::dps);
    LBM.spin(directionType::rev, speed.asDPS(), velocityUnits::dps);
    RBM.spin(directionType::fwd, speed.asDPS(), velocityUnits::dps);
    gyroVal = Inert.rotation(rotationUnits::deg);
  }
  stopDriveHold();
  unHoldDrive();
}

void TurnLeftToHeading(double goal)
{
  TurnLeftToHeading(goal, autonSpeed);
}

void TurnRightToHeading(double goal, Speed speed)
{
  /*
  Method to turn the robot in the clockwise direction using inertial sensor a specific amount
    Uses inertial sensor to initial angle
    Begins turning clockwise at speed indicated
    Continuously checks current angle
    Stops turn when the difference between the current and initial angles equals the intended turn magnitude
      takes into account slight error
  */
  double gyroVal = Inert.rotation(rotationUnits::deg);
  while(gyroVal < (goal-gyroErrHR))
  {
    LFM.spin(directionType::fwd, speed.asDPS(), velocityUnits::dps);
    RFM.spin(directionType::rev, speed.asDPS(), velocityUnits::dps);
    LBM.spin(directionType::fwd, speed.asDPS(), velocityUnits::dps);
    RBM.spin(directionType::rev, speed.asDPS(), velocityUnits::dps);
    gyroVal = Inert.rotation(rotationUnits::deg);
  }
  stopDriveHold();
  unHoldDrive();
}

void TurnRightToHeading(double goal)
{
  TurnRightToHeading(goal, autonSpeed);
}

/*
Scoring Functions
*/

void intakeBall()
{
  /*
  Method to launch a single ball from the flywheel using ultrasonic sensor
    Uses ultrasonic sensor to find distance, x, between sensor and ball
    x decreases as the ball moves up the roller towards the sensor then increases as the ball passes the sensor
    when the ball has been launched, the next one is automatically loaded
    therefore, the ball has been launched once x stops increasing and starts decreasing again
    this point occurs when x goes from increasing to decreasing which happens somewhere where x is concave down
      occurs where dx goes from + to - and where d^2x < 0
  */

  bool ballIn = false;//variable to stop rollers once ball is launched


  //start rollers
  IntakeL.spin(directionType::fwd, INTAKE_SPEED.asPercent(), velocityUnits::pct);
  IntakeR.spin(directionType::fwd, INTAKE_SPEED.asPercent(), velocityUnits::pct);
  RollerL.spin(directionType::fwd, ROLLERL_SPEED.asPercent(), velocityUnits::pct);//slow to move next ball up

  //calculate three values of x using ultrasonic sensor
  double x_0 = Ultrasonic.distance(distanceUnits::mm);
  double x = x_0;
  

  while(!ballIn)
  {

    //calculate new value of x using ultrasonic sensor and update old values
    x = Ultrasonic.distance(distanceUnits::mm);

    //only check for local maximum if x is concave down
    if(x < x_0/2)
    {
      ballIn = true;
    }

    //wait to decrease likelihood of false positive
    wait(50, msec);
  }

  //stops the rollers to only launch one ball
  IntakeL.stop();
  IntakeR.stop();
  RollerL.stop();
}

void intakeBall(int inTime)
{
  //start rollers
  IntakeL.spinFor(directionType::fwd, inTime, timeUnits::msec, INTAKE_SPEED.asPercent(), velocityUnits::pct);
  IntakeR.spinFor(directionType::fwd, inTime, timeUnits::msec, INTAKE_SPEED.asPercent(), velocityUnits::pct);
  RollerL.spinFor(directionType::fwd, inTime, timeUnits::msec, ROLLERL_SPEED.asPercent(), velocityUnits::pct);

  IntakeL.stop();
  IntakeR.stop();
  RollerL.stop();
}

void intakesOn()
{
  IntakeL.spin(directionType::fwd, INTAKE_SPEED.asPercent(), velocityUnits::pct);
  IntakeR.spin(directionType::fwd, INTAKE_SPEED.asPercent(), velocityUnits::pct);
  RollerL.spin(directionType::fwd, ROLLERL_SPEED.asPercent(), velocityUnits::pct);

}

void intakesOut(int inTime)
{
  IntakeL.spin(directionType::rev, INTAKE_SPEED.asPercent(), velocityUnits::pct);
  IntakeR.spin(directionType::rev, INTAKE_SPEED.asPercent(), velocityUnits::pct);
  RollerL.spin(directionType::rev, ROLLERL_SPEED.asPercent(), velocityUnits::pct);
  wait(inTime, msec);
  IntakeL.stop();
  IntakeR.stop();
  RollerL.stop();
}

void intakesOff()
{
  IntakeL.stop();
  IntakeR.stop();
  RollerL.stop();
}

void launchBall()
{
  /*
  Method to launch a single ball from the flywheel using ultrasonic sensor
    Uses ultrasonic sensor to find distance x between sensor and ball
    x decreases as the ball moves up the roller towards the sensor then increases as the ball passes the sensor
    when the ball has been launched, the next one is automatically loaded
    therefore, the ball has been launched once x stops increasing and starts decreasing again
    this point occurs when x goes from increasing to decreasing which happens somewhere where x is concave down
      occurs where dx goes from + to - and where d^2x < 0
  */

  bool ballSent = false;//variable to stop rollers once ball is launched
  bool shouldCheck = false;//variable to check if the ball has been launched


  //start rollers
  RollerU.spin(directionType::fwd, ROLLERU_SPEED.asPercent(), velocityUnits::pct);//fast to launch ball
  RollerL.spin(directionType::fwd, ROLLERL_SPEED_SLOW.asPercent(), velocityUnits::pct);//slow to move next ball up

  //calculate three values of x using ultrasonic sensor
  double x_1 = Ultrasonic.distance(distanceUnits::mm);
  wait(50, msec);
  double x_2 = Ultrasonic.distance(distanceUnits::mm);
  wait(50, msec);
  double x_3 =  Ultrasonic.distance(distanceUnits::mm);

  //calculate two values of dx assuming dt is 1
  double dx_1 = x_2 - x_1;
  double dx_2 = x_3 - x_2;

  //calculate value of d^2x assuming dt^2 is 1
  double d2x = dx_2 - dx_1;

  while(!ballSent)
  {

    //calculate new value of x using ultrasonic sensor and update old values
    x_1 = x_2;
    x_2 = x_3;
    x_3 = Ultrasonic.distance(distanceUnits::mm);

    //calculate two values of dx assuming dt is 1
    dx_1 = x_2 - x_1;
    dx_2 = x_3 - x_2;

    //calculate value of d^2x assuming dt^2 is 1
    d2x = dx_2 - dx_1;

    //check if x is concave down
    if(d2x < 0)
    {
      shouldCheck = true;
    }
    else
    {
      shouldCheck = false;
    }

    //only check for local maximum if x is concave down
    if(shouldCheck)
    {
      //check if x has gone from increasing to decreasing
      if(dx_2 < 0 && dx_1 > 0)
      {
        ballSent = true;
      }
    }

    //wait to decrease likelihood of false positive
    wait(50, msec);
  }

  //stops the rollers to only launch one ball
  wait(50, msec);
  RollerU.stop();
  RollerL.stop();
}

