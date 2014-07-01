#ifndef MOTORS_H
#define MOTORS_H

#define kFullPower 127
#define kHalfPower kFullPower / 2

// Define the default delta setting limit to 256, so that by default a motor
// setting can switch from 127 to -127 in one update cycle, as if there were no
// delta setting limits
#define kDefaultDeltaSettingLimit 256

// For each motor, the actual setting and requested setting are stored, along
// the maximum and minimum amout the setting is allowed to change every cycle.
// This way, the setting may be changed only by a certian amount every cycle.
// The most common use for this feature is to prevent the motor's internal gears
// from stripping because the motor power setting was changed too quickly.
typedef struct {
  short setting;
  short request;
  short min_delta_setting;
  short max_delta_setting;
} Motor;

void MotorsInit();

void MotorsSet(short channel, short setting);

// This function sets the motor on the specified channel to a power setting
// that makes the relationship between motor power setting and actual motor
// speed linear
void MotorsSetAdjusted(short channel, short setting);

void MotorsUpdateTask();

#endif
