#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

motor LFM = motor(PORT14);
motor LBM = motor(PORT11);
motor RFM = motor(PORT12, true);
motor RBM = motor(PORT13, true);
motor IntakeL = motor(PORT3);
motor IntakeR = motor(PORT4, true);
motor RollerL = motor(PORT1);
motor RollerU = motor(PORT2, true);

inertial Inert = inertial(PORT15);

controller Controller = controller();

sonar Ultrasonic = sonar(Brain.ThreeWirePort.A);

void vexcodeInit(void) {
  Inert.startCalibration();
  Brain.Screen.clearScreen();
  while(Inert.isCalibrating())
  {
    Brain.Screen.printAt(30, 30, ((std::string)"[.] Calibrating Gyroscope").c_str());
    wait(500, msec);
  }
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(30, 60, ((std::string)"[+] Gyroscope Calibrated").c_str());
  RollerL.setBrake(brakeType::hold);
  RollerL.stop();
  Brain.Screen.printAt(30, 90, ((std::string)"[+] Brake Set").c_str());
}