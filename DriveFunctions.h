#ifndef DRIVE_FUNCTIONS
#define DRIVE_FUNCTIONS

int toExpo(int& linearInput)
{
	const byte max = 127; //Max motor speeds.
	const int deadZone = 7; //Dead zone amount.
	int drive = pow(1.055, abs(linearInput)) / 7.18 * (linearInput < 0 ? -1 : 1);
	if (drive < deadZone && drive > -deadZone) //If value is in dead zone, change to 0.
	{
		drive = 0;
	}
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
	return drive;
}

void bump(int type, bool forward)
{
	motor[type] = forward ? 80 : -80;
	wait1Msec(10);
	motor[type] = 0;
}

void moveTime(int type, bool forward, int milliseconds)
{
	motor[type] = forward ? 80 : -80;
	wait1Msec(milliseconds);
	motor[type] = 0;
}

void setLeft(int setting)
{
	motor[BackLeft] = setting;
	motor[FrontLeft] = setting;
}

void setRight(int setting)
{
	motor[BackRight] = setting;
	motor[FrontRight] = setting;
}

void resetDriveEncoders()
{
	nMotorEncoder[BackLeft] = 0;
	nMotorEncoder[BackRight] = 0;
  nMotorEncoder[FrontLeft] = 0;
  nMotorEncoder[FrontRight] = 0;
}

#endif
