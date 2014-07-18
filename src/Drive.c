#include "Drive.h"

#include "main.h"
#include "Motors.h"

void DriveInit() {
  
}

void DriveSetLeftPower(short setting) {
  MotorsSetAdjusted(FRONT_LEFT_DRIVE, setting);
  MotorsSetAdjusted(MIDDLE_LEFT_DRIVE, setting);
  MotorsSetAdjusted(BACK_LEFT_DRIVE, setting);
}

void DriveSetRightPower(short setting) {
  MotorsSetAdjusted(FRONT_RIGHT_DRIVE, setting);
  MotorsSetAdjusted(MIDDLE_RIGHT_DRIVE, setting);
  MotorsSetAdjusted(BACK_RIGHT_DRIVE, setting);

}

void DriveSetPower(short setting) {
  DriveSetLeftPower(setting);
  DriveSetRightPower(setting);
}

void DriveMoveStraightTicks(short ticks) {

}

void DrivePivotTicks(short ticks) {

}