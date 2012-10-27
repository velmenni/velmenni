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
 * Sets the values for the shovel's elevation motor(s).
 *
 * value: positive values raise the shovel; negative values lower it.
 */
void setShovelElevationMotors(word value)
{
	// Do nothing for now.
}

/**
 * Sets the values for the shovel's grip motors.
 *
 * value: positive values open the shovel; negative values close it.
 */
void setShovelGripMotors(word value)
{
	// Do nothing for now.
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
	}
}
