#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     LiftTouchHigh,  sensorTouch)
#pragma config(Sensor, S3,     LiftTouchLow,   sensorTouch)
#pragma config(Sensor, S4,     ArmTouch,       sensorTouch)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     BackLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     FrontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Lift,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Arm,           tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     FrontRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     BackRight,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    Scoop,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//ORDER OF WIRING SHOULD BE AS FOLLOWS:
//#1: BACK LEFT , BACK RIGHT
//#2: LIFT      , ARM
//#3: FRONT LEFT, FRONT LEFT
//#4: SCOOP SERVO
#include "JoystickDriver.c"
#include "DriveFunctions.h"
#include "LiftFunctions.h"


task main()
{
	bool tankDrive = false, topHatUp = false, topHatDown = false, speedToggle = false, oldSpeedToggle = false, oldDrive = false;
	const byte max = 127;
	float speedMod = 0;
	int oldTopHatUp = -1, oldTopHatDown = -1;
	//Initialize robot function call.
	initializeRobot();
	//Wait for round to start.
	waitForStart();

	//Autonomous Code Goes Here

	while(true)
	{
		//Get input from controllers.
		getJoystickSettings(joystick);
		//Default. If driver has chosen tank drive, two joysticks control the drive.
		if(tankDrive)
		{
			setLeft(toExpo(joystick.joy1_y1));
			setRight(toExpo(joystick.joy1_y2));
		}
		//If the driver has chosen arcade drive, one joystick controls the drive.
		else
		{
			//Right x value is inverted to decrease and increase when the left x values increase and decrease.
			setLeft(toExpo(joystick.joy1_x1) + toExpo(joystick.joy1_y1));
			setRight(-1 * toExpo(joystick.joy1_x1) + toExpo(joystick.joy1_y1));
		}
		//Button press to change drive system (tank/arcade).
		if(joy1Btn(9) && !oldDrive)
		{
			//When pressed, toggles tank drive (on/off).
			tankDrive = !tankDrive;
		}
		oldDrive = joy1Btn(9);
		//TopHat Position Returns
		//          0
		//        7   1
		//      6  -1   2
		//        5   3
		//          4
		//If upper top hat has been pressed, prep run lift to top.
		if((joystick.joy2_TopHat == 0) && (oldTopHatUp != 0))
		{
			//Stops if lift controls are being used.
			if(toExpo(joystick.joy2_y1) != 0)
			{
				topHatUp = false;
				topHatDown = false;
			}
			//If lift controls are not being used, flag for max speed up lift.
			else
			{
				//Toggles flag for max speed up lift.
				topHatUp = !topHatUp;
				//Ensures that the max speed up and down lift flags cannot be set.
				topHatDown = false;
			}
		}
		oldTopHatUp = joystick.joy2_TopHat;
		//If lower top hat has been pressed, prep run lift to bottom.
		if((joystick.joy2_TopHat == 4) && (oldTopHatDown != 4))
		{
			//Stops if lift controls are being used.
			if(toExpo(joystick.joy2_y1) != 0)
			{
				topHatDown = false;
				topHatUp = false;
			}
			//If lift controls are not being used, flag for max speed down lift.
			else
			{
				//Toggles flag for max speed down lift.
				topHatDown = !topHatDown;
				//Ensures that the max speed up and down lift flags cannot be set.
				topHatUp = false;
			}
		}
		oldTopHatDown = joystick.joy2_TopHat;
		//If flag for max speed up lift is set, run lift up.
		if(topHatUp)
		{
			//Raise lift at max speed.
			motor[Lift] = max;
			//Once button has been pressed, remove flag and bump lift down.
			if(SensorValue(LiftTouchHigh))
			{
				topHatUp = false;
				bump(Lift, false);
			}
		}
		//If flag for max speed down lift is set, run lift down.
		if(topHatDown)
		{
			//Lower lift at max speed.
			motor[Lift] = -max;
			//Once button has been pressed, remove flag and bump lift up.
			if(SensorValue(LiftTouchLow))
			{
				topHatDown = false;
				bump(Lift, true);
			}
		}
		//If button 7 has been pressed, toggle on increased speed.
		if(joy2Btn(7))
		{
			speedToggle = !speedToggle;
		}
		//If button 8 has been pressed, add temporary increased speed.
		if(joy2Btn(8))
		{
			speedMod = 1.2;
			speedToggle = false;
		}
		//Otherwise, keep speed at the same level.
		else
		{
			speedMod = 1;
		}
		//Check to ensure lift is within operating area.
		int liftPos = encoderToLift(nMotorEncoder[Lift]);
		if(liftPos < 98 && liftPos > 2)
		{
			//boostControl(TYPE, SPEEDTOGGLE, CURRENT JOYSTICK READING, SPEEDMOD);
			boostControl(Lift, speedToggle, toExpo(joystick.joy2_y1), speedMod);
		}
		else if(liftPos > 98)
		{
			bump(Lift, false);
		}
		else if(liftPos < 2)
		{
			bump(Lift, true);
		}
		//If the joystick is in use, run boostControl to manage boosting of speed.
		int armPos = encoderToArm(nMotorEncoder[Arm]);
		if(armPos < 98 && armPos > 2)
		{
			//boostControl(TYPE, SPEEDTOGGLE, CURRENT JOYSTICK READING, SPEEDMOD);
			boostControl(Arm, speedToggle, toExpo(joystick.joy2_y2), speedMod);
		}
		else if(armPos > 98)
		{
			bump(Arm, false);
		}
		else if(armPos < 2)
		{
			bump(Arm, true);
		}
		if((joy1Btn(8))&&!(joy1Btn(7))&&!(controllerInUse()))
		{
			turn360('l');
		}
		if((joy1Btn(7))&&!(joy1Btn(8))&&!(controllerInUse()))
		{
			turn360('r');
		}
		//If button 4 is pressed, set servo position up.
		if(joy2Btn(4))
		{
			servo[Scoop] = 0;
		}
		//If button 3 is pressed, set servo position level.
		if(joy2Btn(3))
		{
			servo[Scoop] = 115;
		}
		//If button 3 is pressed, set servo position down.
		if(joy2Btn(2))
		{
			servo[Scoop] = 180;
	 	}
	}
}
