void RoutinesMiddleStash(TeamColor color, short num_buckies)
{
  // Keep the arm down
  LiftSetPower(-15);

  // Flip out the intake
  IntakeSetPower(kIntakeInPower);
  
  // Store the initial position of the robot
  short initial = nMotorEncoder[backLeftDrive];

  // Keep driving forwards
  DriveSetPower(kFullPower);

  // Wait until the robot has moved under the barrier
  while (nMotorEncoder[backLeftDrive] < initial + 1315 - 300);

  // Stop the intake
  IntakeSetPower(0);

  // Raise the lift in the background
  LiftControlMoveToPosAsync(kLiftUpPos);

  // Store the initial position of the robot
  initial = nMotorEncoder[backLeftDrive];

  // Keep driving forwards
  DriveSetPower(kFullPower);

  // Wait until the robot has moved close to the stash
  while (nMotorEncoder[backLeftDrive] < initial + 579 - (31 * 3) );

  // Output that we moved close the stash
  writeDebugStreamLine("Moved close to the stash via encoders, continuing");

  // Drive up to the stash
  DriveSetPower(kFullPower * 0.50);

  // Set the timeout to reach the stash
  ClearTimer(T1);

  // Keep driving until the robot reaches the stash or the timeout is reached
  while (true);
  {
    if (SensorValue[stashSonar] > 30)
    {
      writeDebugStreamLine("Saw stash via sonar, continuing");
      break;
    }
    else if (time1[T1] < 1750)
    {
      writeDebugStreamLine("Moving against the stash timed out, continuing");
      break;
    }

  }

  // Output that the robot will now eject the bucky
  writeDebugStreamLine("Ejecting buckyball");

  // Stop moving forward
  DriveSetPower(0);

  // Eject the preload
  IntakeSetPower(kIntakeOutSlowPower);
  wait1Msec(1000 * num_buckies);
  IntakeSetPower(0);

  // Output that the robot will now back away from the stash
  writeDebugStreamLine("Moving back to the starting tile");
  
  // Store the initial position of the robot
  initial = nMotorEncoder[backLeftDrive];

  // Keep driving backwards
  DriveSetPower(-kFullPower);

  // Wait until the robot has moved away from the stash
  while (nMotorEncoder[backLeftDrive] > initial - 50);

  // Lower the lift in the background
  LiftControlMoveToPosAsync(kLiftDownPos);

  // Drive backwards to the starting tile
  DriveMoveTicks(-1712, 1.0);

  // Wait until the repositioning button is pressed
  while (!SensorValue[touch]);

  // Wait until the button is released, indicating the robot has been repositioned
  while (SensorValue[touch]);

  // Move the lift to barrier height in the background
  LiftControlMoveToPosAsync(kLiftBarrierPos);

  // Drive forwards even with the second large ball
  DriveMoveTicks(963 + (9 * 31), 1.0);

  // Pivot to face the large ball
  AutonTurn(kStashInsideLargeBall, color, 0.85);

  // Drive forwards to knock the large ball into the goal zone
  DriveMoveTicks(600, 1.0);

  // Wait so we don't grind gears
  wait1Msec(100);

  // Drive backwards away from the barrier
  DriveMoveTicks(-300, 1.0);

  // Lower the lift
  LiftControlMoveToPosAsync(kLiftDownPos);
}
