#ifndef LIFT_FUNCTIONS
#define LIFT_FUNCTIONS

int liftToEncoder(int percent)
{
	return(2829 * percent / 400);
}
int armToEncoder(int percent)
{
	return(450 * percent /400);
}
int encoderToLift(int encoder)
{
	return(encoder * 400 / 1414);
}
int encoderToArm(int encoder)
{
	return(encoder * 400 / 900);
}

void boostControl(int type, bool speedToggle, int drive, int speedMod)
{
	const int max = 127;
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
