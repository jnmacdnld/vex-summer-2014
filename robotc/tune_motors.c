#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    liftPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl3,  ,               sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  ,               sensorQuadEncoder)
#pragma config(Sensor, in2,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl7,  touch,          sensorTouch)
#pragma config(Sensor, I2C_1,  backRightDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  backLeftDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           middleLeftDrive, tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port2,           backLeftDrive, tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port3,           frontLeftDrive, tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port4,           leftLift,       tmotorVex393, openLoop)
#pragma config(Motor,  port5,           leftIntake,    tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port6,           backRightDrive, tmotorVex393HighSpeed, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port7,           frontRightDrive, tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port8,           rightLift,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           rightIntake,   tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port10,          middleRightDrive, tmotorVex393HighSpeed, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "tuning.c"
#include "Motors.c"
#include "Drive.c"

void TuneDrive() {
  // Calculate and store the left drive top speed
  float left_drive_top_speed = GetLeftDriveSpeedAtSetting(kFullPower);

  // Calculate and store the right drive top speed
  float right_drive_top_speed = GetRightDriveSpeedAtSetting(kFullPower);

  // Print the left and right drive top speeds
  writeDebugStreamLine("left drive top speed: %d", left_drive_top_speed);
  writeDebugStreamLine("right drive top speed: %d", right_drive_top_speed);

  // The top speed the motors should be tuned to reach should be the lower of
  // the speeds of the two sides of the drive
  if (left_drive_top_speed < right_drive_top_speed)
    max_motor_speed = left_drive_top_speed;
  else
    max_motor_speed = right_drive_top_speed;

  // Print the speed of the slower side
  writeDebugStreamLine("slower drive top speed: %d", max_motor_speed);

  // Tune the left side of the drive
  writeDebugStreamLine("Tuning left side of drive");
  TuneDriveSide(backLeftDrive, middleLeftDrive, frontLeftDrive);

  // Tune the right side of the drive
  writeDebugStreamLine("Tuning right side of drive");
  TuneDriveSide(backRightDrive, middleRightDrive, frontRightDrive);
}

task main() {
  // Tune the drive moving forwards
  writeDebugStreamLine("Tuning the drive moving forwards");
  TuneDrive();

  // Reflect the drive
  DriveReflectLeft();
  DriveReflectRight();

  // Tune the drive moving backwards
  writeDebugStreamLine("Tuning the drive moving backwards");
  TuneDrive();
}
