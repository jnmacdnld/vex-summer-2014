void RoutinesHangingPushMove(TeamColor color)
{
  // Pick up two buckies and push three buckies and a large ball over the bump
  AutonHangingPush(color);

  // Turn towards the starting tile
  AutonTurn(kPushStartTile, color, 0.85);

  // Drive to the starting tile
  DriveSetPower(kFullPower);

  // Set the timer
  ClearTimer(T1);

  // Wait for the signal that the robot reached the wall or the timeout is reached
  while (!SensorValue[frontTouch] && time1[T1] < 1400);
  while (SensorValue[frontTouch]);

  // Stop driving forwards
  DriveSetPower(0);

  // Wait for the robot to be repositioned
  if (color == kBlue)
  {
    while (!SensorValue[touch]);
    while (SensorValue[touch]);
  }    
  else
  {
    while (!SensorValue[frontTouch]);
    while (SensorValue[frontTouch]);
  }

  // Drive into the goal zone
  short ticks = (730 * 3) + 62;
  DriveMoveTicks(-ticks, 1.0);

  // Turn towards the stash
  AutonTurn(kPivotForwards, color, 0.85);
}
