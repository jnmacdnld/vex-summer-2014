#ifndef AUTON
#define AUTON

#include "Auton.h"

#include "LiftControl.c"
#include "Intake.c"
#include "Drive.c"

#include "AutonHangingPush.c"
#include "AutonHangingBlockPush.c"
#include "AutonHangingPushMove.c"
#include "AutonMiddleStash.c"
#include "AutonMiddleBlock.c"
#include "AutonMiddleStashThree.c"
#include "AutonMiddleStashBlock.c"

// Declare encoder movement values
#define kStartToBarrierTicks 671
#define kBarrierToStartTicks -369
#define kToInsideBigBallTicks 851

#define kStartToWall 622
#define kWallToLargeBall -1337

#define kStartUnderBarrierTicks 1679
#define kInFrontOfStashDistance 28
#define kStashUnderBarrier 0
#define kUnderBarrier 0

#define kWallToStashRed 932 + 20
#define kWallToStashBlue 932 - 40

static Auton selected_auton = { kMiddleZone, kBlue };

void AutonInit()
{
  // Set the default zone and team color
  AutonSetZone(kMiddleZone);
  AutonSetColor(kBlue);
}

void AutonSetZone(Zone zone) {
  selected_auton.zone = zone;
}

void AutonSetColor(TeamColor color) {
  selected_auton.color = color;
}

TeamColor AutonGetColor()
{
  return selected_auton.color;
}

Zone AutonGetZone()
{
  return selected_auton.zone;
}

void AutonToggleZone()
{
  if ( AutonGetZone() == kHangingZone )
    AutonSetZone(kMiddleZone);
  else
    AutonSetZone(kHangingZone);
}

void AutonToggleColor()
{
  if ( AutonGetColor() == kRed )
    AutonSetColor(kBlue);
  else
    AutonSetColor(kRed);
}

void AutonSetRoutine(short routine)
{
  selected_auton.routine = routine;
}

short AutonGetRoutine()
{
  return selected_auton.routine;
}

void AutonStepRoutine()
{
  // Store the id of the currently selected routine
  short routine_id = AutonGetRoutine();

  // Declare a variable to store the number of routines
  short num_routines;

  // Set num_routines to the number of routines avaliable for the selected zone
  if ( AutonGetZone() == kMiddleZone )
    num_routines = kNumMiddleRoutines;
  else
    num_routines = kNumHangingRoutines;

  // If the last routine is selected, there is no next routine; select the first
  // routine. Otherwise, there is a next routine; select it.
  if ( routine_id == num_routines - 1)
    AutonSetRoutine(0);
  else
    AutonSetRoutine(routine_id + 1);
}

void AutonRun()
{
  // Reset lift control in case it was active during driver control
  LiftControlReset();

  // Print a message saying AutonRun was called
  writeDebugStreamLine("Call to AutonRun\n");

  // Store the team color
  TeamColor color = AutonGetColor();

  // Print the color of the selected_autonomous
  if (color == kRed)
    writeDebugStreamLine("Autonomous color is red");
  else
    writeDebugStreamLine("Autonomous color is blue");

  // Run the appropriate selected_autonomous routine, passing the color of the robot
  // to the selected_autonomous function
  if ( AutonGetZone() == kHangingZone )
  {
    switch ( AutonGetRoutine() )
    {
      case kPush:
        AutonHangingPush(color);
        break;
      case kBlockAndPush:
        AutonHangingBlockPush(color);
        break;
      case kPushAndMove:
        AutonHangingPushMove(color);
        break;
      default:
        break;
    }
  }
  else
  {
    switch ( AutonGetRoutine() )
    {
      case kStash:
        AutonMiddleStash(color, 1);
        break;
      case kStashAndBlock:
        AutonMiddleStashBlock(color);
        break;
      case kStashThree:
        AutonMiddleStashThree(color);
        break;
      case kBlock:
        AutonMiddleBlock(color);
        break;
      default:
        break;
    }
  }

  // Wait for selected_autonomous to end
  while (true)
    wait1Msec(25);
}

#endif /* AUTON */
