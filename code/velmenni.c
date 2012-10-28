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

/**
 * Sets the values for the left and right drive motors.
 * For each motor, 127 is full speed forward, and -127 is full speed reverse.
 *
 * leftMotor: the value of the left motor.
 * rightMotor: the value of the right motor.
 */
void setMotors(word leftMotor, word rightMotor)
{
	motor[port3] = leftMotor;
	motor[port2] = rightMotor * -1; // reflected.
}

/**
 * Sets the values for the shovel's elevation motors.
 *
 * value: positive values raise the shovel; negative values lower it.
 */
void setShovelElevationMotors(word value)
{
	motor[port10] = value;
	motor[port11] = value;

	motor[port8] = value * -1; // reflected.
	motor[port9] = value * -1; // reflected.
}

/**
 * Sets the values for the shovel's grip motors.
 *
 * value: positive values open the shovel; negative values close it.
 */
void setShovelGripMotors(word value)
{
	motor[port7] = value;
	motor[port6] = value * -1; // reflected.
}

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

  /* Initialize. */
}

task autonomous()
{
	AutonomousCodePlaceholderForTesting();
}

task usercontrol()
{
	while (true)
	{
		/**
		 * Drive control.
		 * Axis 3 (left stick vertical) controls the left side when facing the back.
		 * Axis 2 (right stick vertical) controls the right side when facing the back.
		 * 5U = Turbo (double speed).
		 */
		word speedRatio = vexRT[Btn5U] == 1 ? 1 : 4;
		setMotors(vexRT[Ch3]/speedRatio, vexRT[Ch2]/speedRatio);

#ifdef TWO_CONTROLLERS
		/**
		 * Raise/lower shovel.
		 * C2:Axis 3:positive = Raise; C2:Axis 3:negative = Lower.
		 */
		setShovelElevationMotors(vexRT[Ch3Xmtr2]/2);

		/**
		 * Open/close shovel.
		 * C2:Axis 2:positive = Open; C2:Axis 2:negative = Close.
		 */
		setShovelGripMotors(vexRT[Ch2Xmtr2]/4);
#else
		/**
		 * Raise/lower shovel.
		 * 6U = Raise; 6D = Lower.
		 */
		setShovelElevationMotors((vexRT[Btn6U] ? 64 : 0)
		                       - (vexRT[Btn6D] ? 64 : 0));

		/**
		 * Open/close shovel.
		 * 8R = Open; 8L = Close.
		 */
		setShovelGripMotors((vexRT[Btn8R] ? 32 : 0)
		                  - (vexRT[Btn8L] ? 32 : 0));
#endif
	}
}
