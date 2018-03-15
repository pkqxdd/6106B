#ifndef drivers
#define drivers
#ifndef ever
#define ever ;;
#endif


// -----------------BEGIN Global Constants Configuration-------------------
const int MB_POWER = 127; // power to mobile goal lift
const int FOURBAR_POWER = 90; //power to fourbar
const int CHAINBAR_POWER = 100; // power to chainbar
const int ROLLER_POWER = 100; // power to roller
const int FOURBAR_ANTIGRAVITY = 10; //power to fourbar when it is in the "stop" position
const int MB_ANTIGRAVITY = 0; //power to mobile goal lift when it is in the "stop" position
const int CHAINBAR_ANTIGRAVITY = 20;
const int ROLLER_ANTIGRAVITY = 25;

//POT_MIN is the value when the fourbar is physically at its physical lowest location. MIN may be larger than MAX in value.
//POT_DIRECTION can be either -1 or 1. 1 if the potentiometer reading increase when the structure moves up, -1 otherwise
const int POT_CHAINBAR_MIN = 1200; 
const int POT_CHAINBAR_MAX = 4095;
const int POT_CHAINBAR_DIRECTION=1;


const int POT_FOURBAR_LEFT_DIRECTION = 1;
const int POT_FOURBAR_LEFT_MAX = 3882;
const int POT_FOURBAR_LEFT_MIN = 2150;

const int POT_FOURBAR_RIGHT_DIRECTION = 1; 
const int POT_FOURBAR_RIGHT_MAX = 3703;
const int POT_FOURBAR_RIGHT_MIN = 2060;

const int MB_MIN = 883;
const int MB_MAX = 3260;

const int FRONT_LEFT_DIRECTION = 1;
const int FRONT_RIGHT_DIRECTION = 1;
const int BACK_LEFT_DIRECTION = 1;
const int BACK_RIGHT_DIRECTION = 1;

const int EN_FRONT_LEFT_DIRECTION = -1;
const int EN_FRONT_RIGHT_DIRECTION = -1;

// ------------------END Global Constants Configuration----------------------
// -----------------BEGIN Keymap Configuration------------------

//#include "KeymapSinglePlayer.h"
#include "KeymapTwoPlayer.h"

// -----------------END Keymap Configuration----------------
// ------------------BEGIN Utility Functons---------------

#define min(a, b) ((a)<(b)?(a):(b))
#define max(a, b) ((a)>(b)?(a):(b))
#define and &&
#define or ||
#define not !



bool approxEq(const float a, const float b, const float tolerance)
{
	if (a == b) return true;
	else if (a > b)
	{
		return a - tolerance <= b;
	} else
	{
		return a + tolerance >= b;
	}
}


void moveLeftWheels(const int power)
{
	motor[front_left] = power;
	motor[back_left] = power;
}

void moveRightWheels(const int power)
{
	motor[front_right] = power;
	motor[back_right] = power;
}

void mobileGoalUp()
{
	motor[mb] = MB_POWER;
}


void mobileGoalDown()
{
	motor[mb] = -MB_POWER;
}

void mobileGoalStop()
{
	motor[mb] = 0;
}

void moveMobileGoal(const int power)
{
	motor[mb] = power;
}

void fourBarLeftUp()
{
	motor[fb_left] = FOURBAR_POWER + FOURBAR_ANTIGRAVITY;
}

void fourBarRightUp()
{
	motor[fb_right] = FOURBAR_POWER + FOURBAR_ANTIGRAVITY -
	7;
}

void fourBarMove(const int powerLeft, const int powerRight)
{
	motor[fb_left] = powerLeft;
	motor[fb_right] = powerRight;
}

void fourBarDown()
{
	motor[fb_left] = -FOURBAR_POWER + FOURBAR_ANTIGRAVITY;
	motor[fb_right] = -FOURBAR_POWER + FOURBAR_ANTIGRAVITY+4;
}

void fourBarStop()
{
	motor[fb_left] = FOURBAR_ANTIGRAVITY;
	motor[fb_right] = FOURBAR_ANTIGRAVITY;
}

void rollerIn()
{
	clearTimer(T1);
	while (time1(T1) < 500) motor[roller] = ROLLER_POWER;
}



void rollerOut()
{
	motor[roller] = -ROLLER_POWER;
	//clearTimer(T1);
	//while (time1(T1) < 2500) motor[roller] = -ROLLER_POWER;
}

void rollerStop()
{
	motor[roller] = ROLLER_ANTIGRAVITY;
}

void rollerZero()
{
	motor[roller] = 0;
}

void chainBarUp()
{
	motor[chainbar_left] = CHAINBAR_POWER + CHAINBAR_ANTIGRAVITY;
	motor[chainbar_right] = CHAINBAR_POWER + CHAINBAR_ANTIGRAVITY;

}

void chainBarMove(const int power)
{
	motor[chainbar_left] = power;
	motor[chainbar_right] = power;
}

void chainBarDown()
{
	motor[chainbar_left] = -CHAINBAR_POWER + CHAINBAR_ANTIGRAVITY;
	motor[chainbar_right] = -CHAINBAR_POWER + CHAINBAR_ANTIGRAVITY;
}

void chainBarStop()
{
	motor[chainbar_left] = CHAINBAR_ANTIGRAVITY;
	motor[chainbar_right] = CHAINBAR_ANTIGRAVITY;
}

bool userIntervention(){
	return
	vexRT[Btn5U] or
	vexRT[Btn5D] or
	vexRT[Btn6U] or
	vexRT[Btn6D] or
	vexRT[Btn7U] or
	vexRT[Btn7D] or
	vexRT[Btn7L] or
	vexRT[Btn7R] or
	vexRT[Btn8U] or
	vexRT[Btn8D] or
	vexRT[Btn8L] or
	vexRT[Btn8R] or
	not approxEq(vexRT[Ch1],0,10) or
	not approxEq(vexRT[Ch2],0,10) or
	not approxEq(vexRT[Ch3],0,10) or
	not approxEq(vexRT[Ch4],0,10) or
	vexRT[Btn5UXmtr2] or
	vexRT[Btn5DXmtr2] or
	vexRT[Btn6UXmtr2] or
	vexRT[Btn6DXmtr2] or
	vexRT[Btn7UXmtr2] or
	vexRT[Btn7DXmtr2] or
	vexRT[Btn7LXmtr2] or
	vexRT[Btn7RXmtr2] or
	vexRT[Btn8UXmtr2] or
	vexRT[Btn8DXmtr2] or
	vexRT[Btn8LXmtr2] or
	vexRT[Btn8RXmtr2] or
	not approxEq(vexRT[Ch1Xmtr2],0,10) or
	not approxEq(vexRT[Ch2Xmtr2],0,10) or
	not approxEq(vexRT[Ch3Xmtr2],0,10) or
	not approxEq(vexRT[Ch4Xmtr2],0,10);
}

int chainbarTarget = 0;
int fourbarTarget = 0;
bool isFourBarLocked = false;
bool isChainBarLocked = false;


task lockChainbar()
{ // hold the chainbar in place. Call stoptask to release it
#define currLoc (SensorValue[pot_chainbar]-POT_CHAINBAR_MIN)*POT_CHAINBAR_DIRECTION
	const float kp = 0.1; // proportional constant
	const float ki = 0;
	const float kd = 0; // derivatie constant
	int lastErr, allErr, powerOutput = 0;
	int err = 0;

	for (ever)
	{
		err = chainbarTarget - currLoc;
		powerOutput = CHAINBAR_ANTIGRAVITY + //Base power
		err * kp + // Proportional
		allErr * ki + (lastErr - err) * kd;
		lastErr = err;
		allErr += err;
		chainBarMove(powerOutput);
		abortTimeslice();
	}
#undef currLoc
}


task lockFourBar()
{ // hold the fourbar in place. Call stoptask to release it

#define currLocLeft (SensorValue[pot_fourbar_left] - POT_FOURBAR_LEFT_MIN) * POT_FOURBAR_LEFT_DIRECTION
#define currLocRight (SensorValue[pot_fourbar_right]-POT_FOURBAR_RIGHT_MIN) * POT_FOURBAR_RIGHT_DIRECTION
	const float kp = 0.25; // proportional constant
	const float kd = 0; // derivatie constant
	int lastErrLeft, lastErrRight = 0;
	int powerOutputLeft, powerOutputRight = 0;
	int errLeft, errRight = 0;

	for (ever)
	{
		//POT_MIN is the value when the fourbar is physically at its lowest location
		errLeft = fourbarTarget - currLocLeft;
		errRight = fourbarTarget - currLocRight;

		powerOutputLeft = FOURBAR_ANTIGRAVITY + //Base power
		errLeft * kp + // Proportional
		(lastErrLeft - errLeft) * kd;

		powerOutputRight = FOURBAR_ANTIGRAVITY + //Base power
		errRight * kp + // Proportional
		(lastErrRight - errRight) * kd;

		lastErrLeft = errLeft;
		lastErrRight = errRight;
		fourBarMove(powerOutputLeft, powerOutputRight);
		abortTimeslice();
	}
#undef currLocLeft
#undef currLocRight
}

void releaseChainBar()
{
	isChainBarLocked = false;
	stopTask(lockChainbar);
}

void releaseFourBar()
{
	isFourBarLocked = false;
	stopTask(lockFourBar);
}


void holdChainBar(const int target)
{
	chainbarTarget = target;
	if (isChainBarLocked)
	{
		stopTask(lockChainbar);
	} else
	{
		isChainBarLocked = true;
	}
	startTask(lockChainbar);
	return;

}

void holdChainBar(const int target, const float tolerance)
{
	chainbarTarget = target;
#define currLoc SensorValue[pot_chainbar] - POT_CHAINBAR_MIN
	if (isChainBarLocked)
	{
		stopTask(lockChainbar);
	} else
	{
		isChainBarLocked = true;
	}
	startTask(lockChainbar);
	while (!approxEq(target, currLoc, tolerance))
	{
		//blocks
	}
	return;
#undef currLoc
}

void holdFourBar(const int target)
{
	fourbarTarget = target;
	if (isFourBarLocked)
	{
		stopTask(lockFourBar);
	} else
	{
		isFourBarLocked = true;
	}
	startTask(lockFourBar);
	return;

}

void holdFourBar(const int target, const float tolerance)
{
#define currLocLeft (SensorValue[pot_fourbar_left]-POT_FOURBAR_LEFT_MIN)*POT_FOURBAR_LEFT_DIRECTION
#define currLocRight (SensorValue[pot_fourbar_right]-POT_FOURBAR_RIGHT_MIN)*POT_FOURBAR_RIGHT_DIRECTION
	fourbarTarget = target;
	if (isFourBarLocked)
	{
		stopTask(lockFourBar);
	} else
	{
		isFourBarLocked = true;
	}
	startTask(lockFourBar);
	while (not(approxEq(target,currLocRight , tolerance) and approxEq(target,
		currLocLeft,
	tolerance)))
	{
		//blocks
	};
	return;
#undef currLocLeft
#undef currLocRight
}

void readyForDroppingCone(const int count){
	switch (count)
			{
			case 0:
				holdFourBar(50);
				holdChainBar(2850);
				break;
			case 1:
				holdFourBar(50);
				holdChainBar(2850);
				break;
			case 2:
				holdFourBar(100);
				holdChainBar(2850);
				break;
			case 3:
				holdFourBar(230);
				holdChainBar(2850);
				break;
			case 4:
				holdChainBar(1450, 50);
				holdChainBar(2850);
				holdFourBar(300);
				break;
			case 5:
				holdChainBar(1450, 50);
				holdFourBar(425);
				holdChainBar(2850);

				break;
			case 6:
				holdChainBar(1450, 50);
				holdFourBar(515);
				holdChainBar(2850);

				break;
			case 7:
				holdChainBar(1450, 50);
				holdFourBar(600);
				holdChainBar(2850);

				break;
			case 8:
				holdChainBar(1450, 50);
				holdFourBar(700);
				holdChainBar(2850);

				break;
			case 9:
				holdChainBar(1450, 50);
				holdFourBar(900);
				holdChainBar(2850);
				break;
			}
		}

//----------------END Utility Functions------------

task WheelControls()
{
	for (ever) // a foreverloop
	{
		moveLeftWheels(min(120,AxisLeftWheels));
		moveRightWheels(min(120,AxisRightWheels));
		abortTimeslice();

	}
}

task MobileGoalControls()
{

	for (ever)
	{

		if (ButtonMobileGoalUp)
		{
			mobileGoalUp();
		} else if (ButtonMobileGoalDown)
		{
			mobileGoalDown();
		} else
		{
			mobileGoalStop();
		}


		abortTimeslice();
	}

}

task FourBarControls()
{
	for (ever)
	{
		while (ButtonFourbarUp)
		{
			if (isFourBarLocked) releaseFourBar();
			fourBarLeftUp();
			fourBarRightUp();
		}
		while (ButtonFourbarDown)
		{
			if (isFourBarLocked) releaseFourBar();
			fourBarDown();
		}
		if (!isFourBarLocked) fourBarStop();
		abortTimeslice();
	}
}

task RollerControls()
{
	bool shouldStop = true;
	for (ever)
	{

		if (ButtonRollerOut)
		{
			rollerOut();
			shouldStop = true;

		} else if (ButtonRollerIn)
		{
			rollerIn();
			shouldStop = false;
		} else
		{
			if (shouldStop) rollerZero();
			else rollerStop();
		}
		abortTimeslice();
	}
}

task ChainBarControls()
{
	for (ever)
	{

		while (ButtonChainBarUp)
		{
			if (isChainBarLocked) releaseChainBar();
				chainBarUp();
		}
		while (ButtonChainBarDown)
		{
			if (isChainBarLocked) releaseChainBar();
			chainBarDown();
		}

		if (!isChainBarLocked)
		{
			chainBarStop();


		}
		abortTimeslice();
	}
}

int coneCount = 0;

task SpecialControls()
{
	bool wasPressedIncrement = false;
	bool wasPressedDecrement = false;
	for (ever)
	{
		if (ButtonSpecialPickUp) //aka flat
		{
			holdChainBar(1400);
		}
#ifdef ButtonSpecialDropOffLow
		if (ButtonSpecialDropOffLow)
		{
			holdChainBar(750);
		}
#endif
#ifdef ButtonSpecialDropOffHigh
		if (ButtonSpecialDropOffHigh)
		{
			holdChainBar(2850);
		}
#endif


#ifdef ButtonConeCountIncrement //Added this bunch of ifdef so that even if those buttons are not bound to anything, there is no compiler error
#ifdef ButtonConeCountDecrement


		if (ButtonConeCountIncrement)
		{
			if (!wasPressedIncrement)
			{
				if (coneCount < 10)coneCount++;
				wasPressedIncrement = true;
			}

		} else { wasPressedIncrement = false; }

		if (ButtonConeCountDecrement)
		{
			if (!wasPressedDecrement)
			{
				if (coneCount > 0)
					coneCount--;
				wasPressedDecrement = true;
			}
		} else
		{
			wasPressedDecrement = false;

		}

#ifdef ButtonConeCountReset
		if (ButtonConeCountReset) coneCount = 0;
#endif
#ifdef ButtonSpecialDropOffAdapt
		if (ButtonSpecialDropOffAdapt)
		{
			readyForDroppingCone(coneCount);
		}
#endif
#endif
#endif

		abortTimeslice();
	}
}


#endif
