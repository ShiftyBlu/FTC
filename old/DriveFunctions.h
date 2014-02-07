#ifndef DRIVE_FUNCTIONS
#define DRIVE_FUNCTIONS

int toExpo(int& linearInput)
{
	const int max = 127; //Max motor speeds.
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
//Bump the motor at +/-80 for 10ms.
void bump(int type, bool forward)
{
	motor[type] = forward ? 80 : -80;
	wait1Msec(10);
	motor[type] = 0;
}
//Move the motor at +/-80 for milliseconds ms.
void moveTime(int type, bool forward, int milliseconds)
{
	motor[type] = forward ? 80 : -80;
	wait1Msec(milliseconds);
	motor[type] = 0;
}
//Set full left side drive to setting.
void setLeft(int setting)
{
	motor[BackLeft] = setting;
	motor[FrontLeft] = setting;
}
//Set full right side drive to setting.
void setRight(int setting)
{
	motor[BackRight] = setting;
	motor[FrontRight] = setting;
}
//Set all drive encoders to 0.
void resetDriveEncoders()
{
	nMotorEncoder[BackLeft] = 0;
	nMotorEncoder[BackRight] = 0;
  nMotorEncoder[FrontLeft] = 0;
  nMotorEncoder[FrontRight] = 0;
}
void turn360(char direction)
{
	//if input letter was l (ASCII 108) turn left.
	if (direction == 108)
	{
		setLeft(127);
		setRight(-127);
	}
	//if input letter was r (ASCII 114) turn right.
	else if (direction == 114)
	{
		setLeft(-127);
		setRight(127);
	}
	else {}
}
bool controllerInUse()
{
	bool inUse = false;
	//If the controller is returning any values, will return true.
	if((toExpo(joystick.joy1_y1) != 0)||(toExpo(joystick.joy1_y2) != 0)||(toExpo(joystick.joy1_x1) != 0)||(toExpo(joystick.joy1_x2) != 0))
	{
		inUse = true;
	}
	//If nothing is in use, it will return false.
	else
	{
		inUse = false;
	}
	return(inUse);
}

#endif
