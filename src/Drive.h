#ifndef DRIVE_H
#define DRIVE_H

/**
 * Sets all of the motors on the left side of the drive to the specified power
 * setting
 * @param setting the power setting, -127 to 127, that the motors should be set
 *                to; positive values move the drive forwards; negative values
 *                move the drive backwards
 */
void DriveSetLeftPower(short setting);

/**
 * Sets all of the motors on the right side of the drive to the specified power
 * setting
 * @param setting the power setting, -127 to 127, that the motors should be set
 *                to; positive values move the drive forwards; negative values
 *                move the drive backwards
 */
void DriveSetRightPower(short setting);

/**
 * Sets all of the drive motors to the specified power setting 
 * @param setting the power setting, -127 to 127, that the motors should be set
 *                to; positive values move the drive forwards; negative values
 *                move the drive backwards
 */
void DriveSetPower(short setting);

/**
 * Moves the drive straight, and moves the distance specified in encoder ticks
 * @param ticks         the distance, in ticks, that the drive should move
 */
void DriveMoveStraightTicks(short ticks);

/**
 * Pivots the drive by moving the left side of the drive by the specified amount
 * in encoder ticks while moving the other side of the drive at the same speed
 * but in the opposite direction
 * @param ticks         the distance, in ticks, that the left side of the drive
 *                      should move while pivoting
 */
void DrivePivotTicks(short ticks);

#endif