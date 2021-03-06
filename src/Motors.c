#include "Motors.h"
#include "main.h"

#include <stdlib.h>
#include "MotorLuts.h"

static Motor motors[10];

void MotorsInit() {
  // Initialize the motors array
  for (int i = 0; i < 10; i++) {
    Motor* m = &motors[i];

    m->setting = 0;
    m->request = 0;
    m->max_delta_setting = kDefaultDeltaSettingLimit;
    m->min_delta_setting = -kDefaultDeltaSettingLimit;
  }
}

void MotorsSet(short port, short setting) {
  // Instead of setting the motor power setting directly, set the request and
  // let MotorsUpdateTask decide if that setting is apporiate. This also
  // prevents multiple tasks from calling motorSet, since all calls to
  // motorSet are handled by MotorsUpdateTask
  motors[port].request = setting;
}

void MotorsSetAdjusted(short port, short setting) {
  // Get the motor power setting from the LUT that makes the relationship
  // between motor setting and actual motor speed linear
  short adjusted_setting = MotorLutsGetAdjustedSetting(port, setting);

  MotorsSet(port, adjusted_setting);
}

void MotorsUpdateTask() {
  // Declare a variable to hold the previous wake time to be passed to
  // taskDelayUntil
  unsigned long previous_wake_time;

  // Initialize previous_wake_time with the current system time
  previous_wake_time = millis();

  while (1) {
    // Delay the task for 25 ms cyclically so that other tasks may run (motors
    // only update every 20 ms)
    taskDelayUntil(&previous_wake_time, 25);

    // Update each motor
    for (int i = 0; i < 10; i++) {
      Motor* m = &motors[i];

      short delta_setting = m->request - m->setting;

      // Enforce delta setting limits (motor power setting may only change by
      // a certain amount every update cycle)
      if ( delta_setting > m->max_delta_setting )
        m->setting += m->max_delta_setting;
      else if ( delta_setting < m->min_delta_setting )
        m->setting += m->min_delta_setting;
      else
        m->setting = m->request;

      motorSet(i, m->setting);
    }
  }
}
