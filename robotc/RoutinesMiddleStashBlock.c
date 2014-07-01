void RoutinesMiddleStashBlock(TeamColor color)
{
  // Score two large balls and stash a buckyball
  RoutinesMiddleStash(color, 1);

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
