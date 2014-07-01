void RoutinesMiddleBlock(TeamColor color)
{
  // Move the lift to barrier height in the background
  LiftControlMoveToPosAsync(kLiftBarrierPos);

  short ticks = 0;

  if (color == kBlue)
  {
    ticks = 963 + 120;
  }
  else
  {
    ticks = 963 + 120 - 62;
  }

  // Drive forwards even with the second large ball
  DriveMoveTicks(ticks, 1.0);

  // Pivot to face the large ball
  AutonTurn(kStashInsideLargeBall, color, 0.70);

  // Drive forwards to knock the large ball into the goal zone
  DriveMoveTicks(600, 1.0);

  // Wait so we don't grind gears
  wait1Msec(100);

  // Drive backwards away from the barrier
  DriveMoveTicks(-300, 1.0);

  // Lower the lift
  LiftControlMoveToPosAsync(kLiftDownPos);

  // Set the intake in in case we run into a bucky
  IntakeSetPower(kIntakeInPower);

  // Turn towards the opponent's stash
  AutonTurn(kOpponentStash, color, 0.70);

  // Drive up to the opponent's stash
  DriveMoveTicks(1770, 1.0);

  // Turn to face paralell to the opponent's stash
  AutonTurn(kOpponentStashParalell, color, 0.70);

  // Drive forwards to block the stash
  DriveMoveTicks(477 + (1.5 * 31), 1.0);
}
