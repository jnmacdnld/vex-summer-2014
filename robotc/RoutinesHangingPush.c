void RoutinesHangingPush(TeamColor color)
{
  // Set the intake in to flip it out and get ready to intake the two buckies
  IntakeSetPower(kIntakeInPower);

  // Drive forward to pick up the two buckies
  DriveMoveTicks(kStartToWall);

  // Wait till the buckies are in
  wait1Msec(500);

  // Stop intaking
  IntakeSetPower(0);

  // Turn into position to push a big ball over the bump and knock the three buckies off the bump
  AutonTurn(kHangingLargeBall, color);

  // Push the large ball over the bump and the three buckies with it
  DriveMoveTicks(kWallToLargeBall);
}
