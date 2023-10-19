using namespace vex;

extern brain Brain;
extern motor LFM;
extern motor LBM;
extern motor RFM;
extern motor RBM;
extern motor IntakeL;
extern motor IntakeR;
extern motor RollerL;
extern motor RollerU;
extern inertial Inert;
extern controller Controller;
extern sonar Ultrasonic;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
