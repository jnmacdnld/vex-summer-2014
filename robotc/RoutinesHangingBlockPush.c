void RoutinesHangingBlockPush(TeamColor color)
{
	// Set a timeout to drive across the field to block
  ClearTimer(T1);

  // Store the initial position of the robot
  short initial = nMotorEncoder[backLeftDrive];

  // Start driving backwards
  DriveSetPower(-kFullPower);

  // Wait until the robot has moved to the intended position or the timeout is reached
  while (nMotorEncoder[backLeftDrive] > initial - 2730 && time1[T1] < 2800);

  // Stop moving backwards
  DriveSetPower(0);

  // Turn slightly towards the bump in case the robot is pointing away from the starting tile
  AutonTurn(kBlockTurn, color, 0.85);

  // Move back to the starting tile
  DriveMoveTicks(2330, 1.0);

  // Wait until the repositioning button is pressed
  while (!SensorValue[frontTouch]);

  // Wait until the button is released, indicating the robot has been repositioned
  while (SensorValue[frontTouch]);

  // Set the intake in to flip it out and get ready to intake the two buckies
  IntakeSetPower(kIntakeInPower);

  // Drive forward to pick up the two buckies
  DriveMoveTicks(kStartToWall, 1.0);
  wait1Msec(250);

  // Stop intaking
  IntakeSetPower(0);

  // Drive back to the starting tile
  DriveMoveTicks(-kStartToWall, 1.0);

  /*// Drive backwards even with the buckies on the bump
  DriveMoveTicks(-1001, 1.0);

  // Raise the lift
  LiftControlMoveToPosAsync(kLiftBarrierPos);

  // Pivot to face the buckies
  AutonTurn(kPushBuckies, color, 0.85);

  // Eject the preload into the middle zone
  IntakeSetPower(kIntakeOutFastPower);
  wait1Msec(1000);
  IntakeSetPower(0);

  // Lower the lift
  LiftControlMoveToPosAsync(kLiftDownPos);

  // Drive over the bump, knocking buckies into the middle zone
  DriveMoveTicks(1264, 1.0);*/
}
