void RoutinesMiddleStashThree(TeamColor color)
{
  // Flip out the intake
  IntakeSetPower(kIntakeInPower);

	// Raise the lift
  LiftControlMoveToPosAsync(kLiftBumpPos);

  // Wait until the repo button is pressed and released, indicating the path is clear
  while (!SensorValue[touch]);
  while (SensorValue[touch]);

  // Store the initial position of the robot
  short initial = nMotorEncoder[backLeftDrive];

  // Drive forwards at partial power over the bump
  DriveSetPower(kFullPower * 0.85);

  // Wait until the robot has moved over the bump to the hanging zone start tile
  while (nMotorEncoder[backLeftDrive] < initial + 730 + 62);

  // Move the lift to the floor position
  LiftControlMoveToPosAsync(kLiftDownPos);

  // Pick up the two buckies against the wall
  DriveMoveTicks(kStartToWall, 1.0);

  // Drive back to the starting square
  DriveMoveTicks(-kStartToWall - 730 - 62, 1.0);

  // Wait until the repositioning button is pressed
  while (!SensorValue[touch]);

  // Wait until the button is released, indicating the robot has been repositioned
  while (SensorValue[touch]);

  // Stash three buckyballs and score two large balls
  RoutinesMiddleStash(color, 3);
}
