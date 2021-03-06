#include "Drive.h"

#include "main.h"
#include "Motors.h"
#include "Pid.h"

#define MOVE_STRAIGHT_TICKS_P_GAIN 1.0
#define PIVOT_TICKS_P_GAIN 1.0

static PidController* move_straight_ticks_pid;
static PidController* pivot_ticks_pid;

void DriveInit() {
  move_straight_ticks_pid = PidInitController(MOVE_STRAIGHT_TICKS_P_GAIN, 0.0,
    0.0);
  pivot_ticks_pid = PidInitController(PIVOT_TICKS_P_GAIN, 0.0, 0.0);
}

void DriveSetLeftPower(short setting) {
  MotorsSetAdjusted(FRONT_LEFT_DRIVE, setting);
  MotorsSetAdjusted(MIDDLE_LEFT_DRIVE, setting);
  MotorsSetAdjusted(BACK_LEFT_DRIVE, setting);
}

void DriveSetRightPower(short setting) {
  // In order for positive values of setting to move the drive forwards, 
  // the motors must be set to -setting
  MotorsSetAdjusted(FRONT_RIGHT_DRIVE, -setting);
  MotorsSetAdjusted(MIDDLE_RIGHT_DRIVE, -setting);
  MotorsSetAdjusted(BACK_RIGHT_DRIVE, -setting);
}

void DriveSetPower(short setting) {
  DriveSetLeftPower(setting);
  DriveSetRightPower(setting);
}

void DriveMoveStraightTicks(short ticks) {
  long current_ime_ticks;
  short pid_calculated_power;

  // Store the value of the back left IME in current_ime_ticks
  imeGet(BACK_LEFT_DRIVE_IME, &current_ime_ticks);

  move_straight_ticks_pid->target = current_ime_ticks + ticks;

  while (move_straight_ticks_pid->error != 0) {
    // Store the value of the back left IME in current_ime_ticks
    imeGet(BACK_LEFT_DRIVE_IME, &current_ime_ticks);
    
    pid_calculated_power = PidGetPower(move_straight_ticks_pid,
      current_ime_ticks);
    DriveSetPower(pid_calculated_power);
  }
}

void DrivePivotTicks(short ticks) {
  long current_ime_ticks;
  short pid_calculated_power;

  // Store the value of the back left IME in current_ime_ticks
  imeGet(BACK_LEFT_DRIVE_IME, &current_ime_ticks);

  pivot_ticks_pid->target = current_ime_ticks + ticks;

  while (pivot_ticks_pid->error != 0) {
    // Store the value of the back left IME in current_ime_ticks
    imeGet(BACK_LEFT_DRIVE_IME, &current_ime_ticks);
    
    pid_calculated_power = PidGetPower(pivot_ticks_pid,
      current_ime_ticks);
    DriveSetLeftPower(pid_calculated_power);
    DriveSetRightPower(-pid_calculated_power);
  }
}