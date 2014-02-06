#ifndef LIFT_FUNCTIONS
#define LIFT_FUNCTIONS
#include "DriveFunctions.h"

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
#endif
