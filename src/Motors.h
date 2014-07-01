#ifndef MOTORS_H
#define MOTORS_H

#define kFullPower 127
#define kHalfPower kFullPower / 2

#define kDefaultAccelLimit 256

typedef struct {
  short setting;
  short request;
  short min_delta_setting;
  short max_delta_setting;
} Motor;

void MotorsInit();

void MotorsSet(short channel, short setting);
void MotorsSetAdjusted(short channel, short setting);

void MotorsUpdateTask();

#endif
