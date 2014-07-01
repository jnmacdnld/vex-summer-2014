#include "Auton.h"
#include "AutonTurn.h"

static short auton_turns[kNumAutonTurns][2];
static int AutonGetTurnTicks(Turn turn, TeamColor color);

void AutonTurnInitTurns()
{
  // Set encoder turn values for the middle zone stash autonomous
  auton.turns[kStashInsideLargeBall][kRed] = -330;
  auton.turns[kStashInsideLargeBall][kBlue] = 460;

  auton.turns[kOpponentStash][kRed] = 100;
  auton.turns[kOpponentStash][kBlue] = -150 - 30;

  auton.turns[kOpponentStashParalell][kRed] = 230;
  auton.turns[kOpponentStashParalell][kBlue] = -300 / 2;

  // Set values for legacy middle zone autonomous
  auton.turns[kInsideBigBall][kRed] = 231;
  auton.turns[kInsideBigBall][kBlue] = -184;

  // Set values for the hanging zone push autonomous
  auton.turns[kHangingLargeBall][kBlue] = -290;
  auton.turns[kHangingLargeBall][kRed] = 205; // FIX ME

  auton.turns[kBlockTurn][kBlue] = -330 / 4;
  auton.turns[kBlockTurn][kRed] = 430 / 4;

  auton.turns[kPushStartTile][kBlue] = -330 / 3;
  auton.turns[kPushStartTile][kRed] = 430 / 3;

  // Set values for the legacy hanging zone stash autonomous
  auton.turns[kPivotForwards][kBlue] = 723;
  auton.turns[kPivotForwards][kRed] = -810;

  auton.turns[kPivotInside][kBlue] = -301;
  auton.turns[kPivotInside][kRed] = 447;

  auton.turns[kPivotStash][kBlue] = 444 - 10;
  auton.turns[kPivotStash][kRed] = -404 + 30;

  // Set values for the hanging zone block and push autonomous
  auton.turns[kPushBuckies][kBlue] = -300;
  auton.turns[kPushBuckies][kRed] = 460;
}

int AutonGetTurnTicks(Turn turn, TeamColor color)
{
  return auton.turns[turn][color];
}

void AutonTurn(Turn turn, TeamColor color, float percent)
{
  DriveTurnTicks( AutonGetTurnTicks(turn, color), percent );
}
