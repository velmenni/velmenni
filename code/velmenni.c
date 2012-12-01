/**
 * Copyright (C) 2012 Velmenni. All rights reserved.
 *
 * vim:noet
 */

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
//#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"		//Main competition background code...do not modify!

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
	motor[port9] = leftMotor;
	motor[port8] = rightMotor * -1; // reflected.
}

/**
 * Sets the values for the spatula's elevation motors.
 *
 * value: positive values raise the spatula; negative values lower it.
 */
void setSpatulaElevationMotors(word value)
{
	motor[port7] = value;
	motor[port6] = value;

	motor[port5] = value * -1; // reflected.
	motor[port4] = value * -1; // reflected.
}

/**
 * Sets the values for the spatula's pitch adjustment motors.
 *
 * value: positive values increase pitch; negative values decrease it.
 */
void setSpatulaPitchMotors(word value)
{
	motor[port3] = value;
	motor[port2] = value * -1; // reflected.
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

float speedDivisor = 1.0;
float spatulaSpeedDivisor = 1.0;

task speedAdjustment() {
	while (true) {
		/* Gradual adjustment of limit via button 5U. */
		if (vexRT[Btn5U] && speedDivisor < 4.0) {
			speedDivisor += 0.05;
		} else if (!vexRT[Btn5U] && speedDivisor > 1.0) {
			speedDivisor -= 0.05;
		}

#ifdef TWO_CONTROLLERS
		/* Gradual adjustment of spatula limit via button 5D. */
		if (vexRT[Btn5DXmtr2] && spatulaSpeedDivisor < 4.0) {
			spatulaSpeedDivisor += 0.025;
		} else if (!vexRT[Btn5DXmtr2] && spatulaSpeedDivisor > 1.0) {
			spatulaSpeedDivisor -= 0.025;
		}
#else
		/* Gradual adjustment of spatula limit via button 5D. */
		if (vexRT[Btn5D] && spatulaSpeedDivisor < 4.0) {
			spatulaSpeedDivisor += 0.025;
		} else if (!vexRT[Btn5D] && spatulaSpeedDivisor > 1.0) {
			spatulaSpeedDivisor -= 0.025;
		}
#endif

		Sleep(10);
	}
}

task usercontrol()
{
	StartTask(speedAdjustment);

	while (true)
	{
		/**
		 * Drive control.
		 * Axis 3 (left stick vertical) controls the left side when facing the back.
		 * Axis 2 (right stick vertical) controls the right side when facing the back.
		 * 5U = Limit (half speed). Gradual. See 'speedAdjustment' task.
		 */
		setMotors(vexRT[Ch3]/speedDivisor, vexRT[Ch2]/speedDivisor);

#ifdef TWO_CONTROLLERS
		/**
		 * Raise/lower shovel.
		 * C2:Axis 3:positive = Raise; C2:Axis 3:negative = Lower.
		 */
		setSpatulaElevationMotors(vexRT[Ch3Xmtr2]/2/spatulaSpeedDivisor);

		/**
		 * Adjust spatula pitch.
		 * C2:Axis 2:positive = Raise; C2:Axis 2:negative = Lower.
		 */
		setSpatulaPitchMotors(vexRT[Ch2Xmtr2]/2/spatulaSpeedDivisor);
#else
		/**
		 * Raise/lower spatula.
		 * 6U = Raise; 6D = Lower.
		 */
		setSpatulaElevationMotors((vexRT[Btn6U] ? 64 : 0)/spatulaSpeedDivisor
		                        - (vexRT[Btn6D] ? 64 : 0)/spatulaSpeedDivisor);

		/**
		 * Adjust spatula pitch.
		 * 8U = Raise; 8D = Lower.
		 */
		setSpatulaPitchMotors((vexRT[Btn8U] ? 64 : 0)/spatulaSpeedDivisor
		                    - (vexRT[Btn8D] ? 64 : 0)/spatulaSpeedDivisor);
#endif
	}
}
