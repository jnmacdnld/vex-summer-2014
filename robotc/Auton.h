// Stores the currently selected autonomous routine and runs that routine
// when AutonRun is called

#ifndef AUTON_H
#define AUTON_H

// Declare IDs for each autonomous routine
#define kPush 0
#define kBlockAndPush 1
#define kPushAndMove 2

#define kStash 0
#define kStashAndBlock 1
#define kStashThree 2
#define kBlock 3

// Declare the number for autonomous routines avaliable for each zone
#define kNumMiddleRoutines 4
#define kNumHangingRoutines 3

// Declare an enum for the robot's team color
typedef enum { kRed, kBlue } TeamColor;

// Declare an enum for the robot's zone
typedef enum { kHangingZone, kMiddleZone } Zone;

// Declare a struct to hold data about an autonomous routine
typedef struct
{
  Zone zone;
  TeamColor color;
  short routine;
} Auton;

void AutonInit();

void AutonSetZone(Zone zone);
Zone AutonGetZone();
void AutonToggleZone();

void AutonSetColor(TeamColor color);
TeamColor AutonGetColor();
void AutonToggleColor();

void AutonSetRoutine(short routine);
short AutonGetRoutine();
void AutonStepRoutine();

void AutonRun();

#endif
