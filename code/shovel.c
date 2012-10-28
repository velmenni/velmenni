/**
 * Copyright (C) 2012 Velmenni. All rights reserved.
 *
 * vim:noet
 */

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
