#ifndef LIFT_FUNCTIONS
#define LIFT_FUNCTIONS

void armBump(int direction)
{
	//If direction is a negative value, bump in positive direction.
	if(direction < 0)
	{
		bump(Arm, true);
	}
	//If direction is a positive value, bump in negative direction.
	else if (direction > 0)
	{
		bump(Arm, false);
	}
}
void boostControl(int type, bool speedToggle, int drive, int speedMod)
{
	const byte max = 127;
	if(speedToggle)
	{
		drive = (drive*1.2);
		//If output is beyond motor input, set to max.
		if (drive > max)
		{
			drive = max;
		}
		//If output is beyond motor -input, set to -max.
		if (drive < -max)
		{
			drive = -max;
		}
		motor[type] = drive;
	}
	//If speed toggle is not on, run normal drive.
	else
	{
		drive = (drive*speedMod);
		//If output is beyond motor input, set to max.
		if (drive > max)
		{
			drive = max;
		}
		//If output is beyond motor -input, set to -max.
		if (drive < -max)
		{
			drive = -max;
		}
		motor[type] = drive;
	}
}
#endif
