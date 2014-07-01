// Stores encoder turn values for each turn in each autonomous routine

#ifndef AUTON_TURN_H
#define AUTON_TURN_H

// Declare number of autonomous turns to store encoder turn values for
#define kNumAutonTurns 11

// Declare an enum for the turns
typedef enum
{
  kInsideBigBall, kHangingLargeBall, kPivotForwards, kPivotInside,
  kPivotStash, kStashInsideLargeBall, kPushBuckies, kOpponentStash,
  kOpponentStashParalell, kBlockTurn, kPushStartTile
} Turn;

void AutonTurn(Turn turn, TeamColor color, float percent = 0.7);
void AutonTurnInitTurns();

#endif
