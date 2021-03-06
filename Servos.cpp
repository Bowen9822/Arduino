#include "Servos.h"

// servo angles for robot arms
constexpr uint16_t DEFAULT_LEFT_ARM_SERVO_ANGLE =           80;
constexpr uint16_t LOWERED_LEFT_ARM_SERVO_ANGLE =           180;
constexpr uint16_t RAISED_LEFT_ARM_SERVO_ANGLE =            25;

constexpr uint16_t DEFAULT_LEFT_CLAW_SERVO_ANGLE =          105;
constexpr uint16_t OPEN_LEFT_CLAW_SERVO_ANGLE =             180;
constexpr uint16_t CLOSED_LEFT_CLAW_SERVO_ANGLE =           55;

constexpr uint16_t DEFAULT_RIGHT_ARM_SERVO_ANGLE =          90;
constexpr uint16_t LOWERED_RIGHT_ARM_SERVO_ANGLE =          1;
constexpr uint16_t RAISED_RIGHT_ARM_SERVO_ANGLE =           127;

constexpr uint16_t DEFAULT_RIGHT_CLAW_SERVO_ANGLE =         80;
constexpr uint16_t OPEN_RIGHT_CLAW_SERVO_ANGLE =            13;
constexpr uint16_t CLOSED_RIGHT_CLAW_SERVO_ANGLE =          116;


// servo angles for bridge drops
constexpr uint16_t DEFAULT_LEFT_BRIDGE_SERVO_ANGLE =        85;
constexpr uint16_t DEFAULT_RIGHT_BRIDGE_SERVO_ANGLE =       90;
constexpr uint16_t DROP_BRIDGE1_LEFT_BRIDGE_SERVO_ANGLE =   0;
constexpr uint16_t DROP_BRIDGE1_RIGHT_BRIDGE_SERVO_ANGLE =  180;
constexpr uint16_t DROP_BRIDGE2_LEFT_BRIDGE_SERVO_ANGLE =   85;
constexpr uint16_t DROP_BRIDGE2_RIGHT_BRIDGE_SERVO_ANGLE =  90;


// delay between movements
constexpr uint16_t SWEEP_DELAY_MS =                         10;
constexpr uint16_t MOVEMENT_DELAY_MS =                      500;
constexpr uint16_t BRIDGE_DROP_DELAY_MS =                   2000;


// servo objects for control
ServoTINAH leftArm;
ServoTINAH leftClaw;
ServoTINAH rightArm;
ServoTINAH rightClaw;
ServoTINAH leftBridge;
ServoTINAH rightBridge;


void detachServos(void){
  leftArm.detach();
  leftClaw.detach();
  rightArm.detach();
  rightClaw.detach();
  leftBridge.detach();
  rightBridge.detach();
}


void initializeServos(void) {
  leftArm.attach(LEFT_ARM_SERVO);
  leftClaw.attach(LEFT_CLAW_SERVO);
  rightArm.attach(RIGHT_ARM_SERVO);
  rightClaw.attach(RIGHT_CLAW_SERVO);
  leftBridge.attach(LEFT_BRIDGE_SERVO);
  rightBridge.attach(RIGHT_BRIDGE_SERVO);

  leftArm.write(DEFAULT_LEFT_ARM_SERVO_ANGLE);
  leftClaw.write(DEFAULT_LEFT_CLAW_SERVO_ANGLE);
  rightArm.write(DEFAULT_RIGHT_ARM_SERVO_ANGLE);
  rightClaw.write(DEFAULT_RIGHT_CLAW_SERVO_ANGLE);
  leftBridge.write(DEFAULT_LEFT_BRIDGE_SERVO_ANGLE);
  rightBridge.write(DEFAULT_RIGHT_BRIDGE_SERVO_ANGLE);

  delay(MOVEMENT_DELAY_MS);
  detachServos();
}


// initialization routines sets up claw corresponding claw to pick up objects
void initializeRightClaw(void) {
  rightArm.attach(RIGHT_ARM_SERVO);
  rightClaw.attach(RIGHT_CLAW_SERVO);

  rightClaw.write(OPEN_RIGHT_CLAW_SERVO_ANGLE);
  delay(MOVEMENT_DELAY_MS);
  rightArm.write(LOWERED_RIGHT_ARM_SERVO_ANGLE);
  delay(MOVEMENT_DELAY_MS);
}


void initializeLeftClaw(void) {
  leftArm.attach(LEFT_ARM_SERVO);
  leftClaw.attach(LEFT_CLAW_SERVO);

  leftClaw.write(OPEN_LEFT_CLAW_SERVO_ANGLE);
  delay(MOVEMENT_DELAY_MS);
  leftArm.write(LOWERED_LEFT_ARM_SERVO_ANGLE);
  delay(MOVEMENT_DELAY_MS);
}


// routines for picking up objects, leaves claw in default positions after
void pickUpRightSide(void) {
  for (int angle = OPEN_RIGHT_CLAW_SERVO_ANGLE; angle < CLOSED_RIGHT_CLAW_SERVO_ANGLE; angle++) {
    rightClaw.write(angle);
    delay(SWEEP_DELAY_MS);
  }
  
  rightArm.write(RAISED_RIGHT_ARM_SERVO_ANGLE);
  delay(MOVEMENT_DELAY_MS);
  rightClaw.write(OPEN_RIGHT_CLAW_SERVO_ANGLE);
  delay(MOVEMENT_DELAY_MS);

  rightClaw.write(DEFAULT_RIGHT_CLAW_SERVO_ANGLE);
  rightArm.write(DEFAULT_RIGHT_ARM_SERVO_ANGLE);
  delay(MOVEMENT_DELAY_MS);

  rightArm.detach();
  rightClaw.detach();
}


void pickUpLeftSide(void) {
  for (int angle = OPEN_LEFT_CLAW_SERVO_ANGLE; angle > CLOSED_LEFT_CLAW_SERVO_ANGLE; angle--) {
    leftClaw.write(angle);
    delay(SWEEP_DELAY_MS);
  }
  
  leftArm.write(RAISED_LEFT_ARM_SERVO_ANGLE);
  delay(MOVEMENT_DELAY_MS);
  leftClaw.write(OPEN_LEFT_CLAW_SERVO_ANGLE);
  delay(MOVEMENT_DELAY_MS);

  leftClaw.write(DEFAULT_LEFT_CLAW_SERVO_ANGLE);
  leftArm.write(DEFAULT_LEFT_ARM_SERVO_ANGLE);
  delay(MOVEMENT_DELAY_MS);

  leftArm.detach();
  leftClaw.detach();
}


// bridge routines
void dropFirstBridge(void) {
  leftBridge.attach(LEFT_BRIDGE_SERVO);
  rightBridge.attach(RIGHT_BRIDGE_SERVO);

  leftBridge.write(DROP_BRIDGE1_LEFT_BRIDGE_SERVO_ANGLE);
  rightBridge.write(DROP_BRIDGE1_RIGHT_BRIDGE_SERVO_ANGLE);
  delay(BRIDGE_DROP_DELAY_MS);
  
  leftBridge.detach();
  rightBridge.detach();
}

void dropSecondBridge(void) {
  leftBridge.attach(LEFT_BRIDGE_SERVO);
  rightBridge.attach(RIGHT_BRIDGE_SERVO);
  
  leftBridge.write(DROP_BRIDGE2_LEFT_BRIDGE_SERVO_ANGLE);
  rightBridge.write(DROP_BRIDGE2_RIGHT_BRIDGE_SERVO_ANGLE);
  delay(BRIDGE_DROP_DELAY_MS);

  leftBridge.detach();
  rightBridge.detach();
}
