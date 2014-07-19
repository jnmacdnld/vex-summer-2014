#ifndef PID_H
#define PID_H

#define kDefaultErrorThreshold 10
#define kDefaultIntegralTermLimit 0.25

typedef struct {
  // Give the option of storing an error threshold to prevent overshoot
  short error_threshold;

  // In order to calculate the derivate term, a variable to store the error from
  // the last iteration of the PID loop is needed
  short last_error;

  // Give the option of storing an integral term limit to prevent windup
  float integral_term_limit;

  int error_integral;
  short target_value;

  float p_gain;
  float i_gain;
  float d_gain;
} PidController;

/**
 * Runs one iteration of the PID control loop and returns the outputted motor
 * power setting
 * @param  p            pointer to the PidController to update, returned by
 *                      PidInitController
 * @param  sensor_value the value of the sensor monitoring the process regulated
 *                      by the PID loop (for example, the value of an encoder
 *                      connected to a drive shaft)
 * @return              the motor power setting outputted by the PID controller
 */
short PidGetPower(PidController* p, short sensor_value);

/**
 * Initializes a PID controller struct with the given parameters and returns a
 * pointer to that struct
 * @param  p_gain the propotional gain constant, a number between 0.0 and 1.0
 * @param  i_gain the integral gain constant, a number between 0.0 and 1.0
 * @param  d_gain the derivative gain constant, a number between 0.0 and 1.0
 * @return        a pointer to the new PID controller struct, and NULL if there
 *                are already kMaxPidControllers controllers intialized
 */
PidController* PidInitController(float p_gain, float i_gain, float d_gain);

#endif
