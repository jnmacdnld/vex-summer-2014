#include "ArcadeDrive.h"

#include "Drive.c"
#include "Joystick.c"

static int ArcadeDriveGetSlowSidePower(int fast_side_power, int turn_stick_value);
static int left_drive_power, right_drive_power;

void ArcadeDriveUpdate()
{
  // Read the joystick
  int speed_stick_value = JoystickGet(kLeftStickYAxis);
  int turn_stick_value = JoystickGet(kRightStickXAxis);
 
  // If the speed stick has not been moved,
  // pivot turn according to the turn stick
  if (speed_stick_value == 0)
  {
    // Set the drive to move clockwise when the turn stick is moved to the right
    // and counterclockwise when it is moved to the left
    left_drive_power = turn_stick_value;
    right_drive_power = -turn_stick_value;
 
    // Set the drive power
    DriveSetLeft(left_drive_power);
    DriveSetRight(right_drive_power);
  }
  else
  {
    // If the speed stick has been moved, curve turn accoring to the turn stick
    // To curve turn, one side will be faster than the other
 
    // The fast side is set from the speed stick
    short fast_side_power = speed_stick_value;
 
    // The slow side is set as a fraction of the fast side; the more the turn
    // stick is moved, the smaller that fraction will be and the slower the slow
    // side will go
    short slow_side_power = ArcadeDriveGetSlowSidePower(speed_stick_value, turn_stick_value);
 
    // In order to make the curve turn consistent with the pivot turn,
    // each case needs to be worked out so that it will turn clockwise by pushing
    // the turn stick the right, and counterclockwise to the left
    if (turn_stick_value > 0 && speed_stick_value > 0 ||
        turn_stick_value < 0 && speed_stick_value < 0)
    {
      DriveSetLeft(fast_side_power);
      DriveSetRight(slow_side_power);
    }
    else
    {
      DriveSetLeft(slow_side_power);
      DriveSetRight(fast_side_power);
    }
  }
}

int ArcadeDriveGetSlowSidePower(int fast_side_power, int turn_stick_value)
{
  // The relationship between the amount the turn stick has been moved and the
  // speed of the slow side is linear
 
  // Cast to float for precise calculation
  float fast_side_power_f = (float) fast_side_power;
  float turn_stick_value_f = (float) turn_stick_value;
 
  // Linear equation in y = mx + b form
  float slow_side_power = -(fast_side_power_f / 127) * turn_stick_value_f + fast_side_power;
 
  // Motor power values must be integers
  return (int) slow_side_power;
}
