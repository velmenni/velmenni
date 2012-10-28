/**
 * Copyright (C) 2012 Velmenni. All rights reserved.
 *
 * vim:noet
 */

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(OFF)
//#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/**
 * If defined, the two controller scheme is used.
 * One player controls the driving, while the other controls
 * the shovel.
 */
//#define TWO_CONTROLLERS

#include "drive.c"
#include "shovel.c"

#include "pre_auton.c"
#include "autonomous.c"
#include "usercontrol.c"
