#ifndef MOTOR_LUTS_H
#define MOTOR_LUTS_H

/**
 * Adjusts the supplied motor power setting and returns the adjusted setting so
 * that the relationship between motor power setting and actual motor speed is
 * linear. The value of the adjusted motor power setting is taken from a lookup
 * table.
 * 
 * If a motor power setting is not adjusted before being passed to motorSet,
 * the relationship between motor power setting and actual motor speed will be
 * logarithmic, not linear. This leads to poor control loop performance and
 * rather unintuitive driving; as the joystick is pressed forwards, the robot
 * at first accelerates very quickly and then very slowly.
 * 
 * @param port the port that the motor is connected to that will be set to the
 * adjusted power setting
 * @param setting the setting to adjust
 * @return the adjusted motor power setting
 */
short MotorLutsGetAdjustedSetting(short port, short setting);

/**
 * Initialize the LUTs
 */
void MotorLutsInit();

#endif
