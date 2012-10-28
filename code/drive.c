/**
 * Copyright (C) 2012 Velmenni. All rights reserved.
 *
 * vim:noet
 */

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
