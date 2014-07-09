#include "Pid.h"

#include <stdio.h>
#include <stdlib.h>
#include "Motors.h"

short PidUpdateController(PidController* p, short sensor_value) {
  double output, integral_term;
  short error, error_derivative;

  error = p->target_value - sensor_value;

  // Set error to zero if it falls below the threshold
  if (abs(error) < p->error_threshold)
    error = 0;

  p->error_integral += error;

  integral_term = p->error_integral * p->i_gain;

  // Bound integral term between -integral_term_limit and intergral_term_limit
  if (integral_term > p->integral_term_limit)
    integral_term = p->integral_term_limit;
  if (integral_term < -p->integral_term_limit)
    integral_term = -p->integral_term_limit;

  error_derivative = error - p->last_error;

  // Store the current error in last_error so that the derivative may be
  // calculated in the next iteration
  p->last_error = error;

  // Set the output to the sum of the propotional, integral, and derivative terms
  output = (error * p->p_gain) + integral_term + (error_derivative * p->d_gain);

  // Bound output between 1.0 and -1.0
  if (output > 1.0)
    output = 1.0;
  if (output < -1.0)
    output = -1.0;

  // Scale the output up to the motor power settings (between kMaxMotorPower
  // and -kMaxMotorPower)
  output *= kMaxMotorPower;

  return (short) output;
}

PidController* PidInitController(float p_gain, float i_gain, float d_gain) {
  // Allocate memory for a PID controller struct and store a pointer to that memory
  PidController* p = (PidController*) malloc( sizeof(PidController) );

  // Initialize PID variables to their default values
  p->error_threshold = kDefaultErrorThreshold;
  p->last_error = 0;
  p->integral_term_limit = kDefaultIntegralTermLimit;
  p->target_value = 0;

  // Set the gain constants from the parameters
  p->p_gain = p_gain;
  p->i_gain = i_gain;
  p->d_gain = d_gain;

  return p;
}
