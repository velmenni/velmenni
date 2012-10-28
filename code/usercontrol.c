/**
 * Copyright (C) 2012 Velmenni. All rights reserved.
 *
 * vim:noet
 */

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
