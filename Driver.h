#ifndef drivers
#define drivers
#ifndef ever
#define ever ;;
#endif


// -----------------BEGIN Global Constants Configuration-------------------
const int MB_POWER = 127; // power to mobile goal lift
const int FOURBAR_POWER = 90; //power to fourbar
const int CHAINBAR_POWER = 80; // power to chainbar
const int ROLLER_POWER = 100; // power to roller
const int FOURBAR_ANTIGRAVITY = 10; //power to fourbar when it is in the "stop" position
const int MB_ANTIGRAVITY = 0; //power to mobile goal lift when it is in the "stop" position
const int CHAINBAR_ANTIGRAVITY = 20;
const int ROLLER_ANTIGRAVITY = 20;

const int POT_CHAINBAR_MIN = 0;
const int POT_CHAINBAR_MAX = 2050;

//POT_MIN is the value when the fourbar is physically at its lowest location. MIN may be larger than MAX in value.
const int POT_FOURBAR_LEFT_DIRECTION = -1;
const int POT_FOURBAR_LEFT_MAX = 672;
const int POT_FOURBAR_LEFT_MIN = 2030;

const int POT_FOURBAR_RIGHT_DIRECTION = 1;
const int POT_FOURBAR_RIGHT_MAX = 2894;
const int POT_FOURBAR_RIGHT_MIN = 1550;

const int MB_MIN = 883;
const int MB_MAX = 3260;

const int FRONT_LEFT_DIRECTION = 1;
const int FRONT_RIGHT_DIRECTION = 1;
const int BACK_LEFT_DIRECTION = 1;
const int BACK_RIGHT_DIRECTION = 1;

const int EN_FRONT_LEFT_DIRECTION = -1;
const int EN_FRONT_RIGHT_DIRECTION = -1;
const int EN_MAX = 3200;
const int EN_MIN = 940;

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
	4.25;
}

void fourBarMove(const int powerLeft, const int powerRight)
{
	motor[fb_left] = powerLeft;
	motor[fb_right] = powerRight;
}

void fourBarDown()
{
	motor[fb_left] = -FOURBAR_POWER + FOURBAR_ANTIGRAVITY;
	motor[fb_right] = -FOURBAR_POWER + FOURBAR_ANTIGRAVITY;
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
	motor[chainbar_left] = power;

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

void chainBarStay()
{
	motor[chainbar_left] = min(CHAINBAR_ANTIGRAVITY, (SensorValue[pot_chainbar] - 1200) * 0.15);
	motor[chainbar_right] = min(CHAINBAR_ANTIGRAVITY, (SensorValue[pot_chainbar] - 1200) * 0.15);

}


int chainbarTarget = 0;
int fourbarTarget = 0;
bool isFourBarLocked = false;
bool isChainBarLocked = false;


task lockChainbar()
{ // hold the chainbar in place. Call stoptask to release it
#define currLoc SensorValue[pot_chainbar]
	const float kp = -0.2; // proportional constant
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

#define currLocLeft SensorValue[pot_fourbar_left]
#define currLocRight SensorValue[pot_fourbar_right]
	const float kp = 0.25; // proportional constant
	const float kd = 0; // derivatie constant
	int lastErrLeft, lastErrRight = 0;
	int powerOutputLeft, powerOutputRight = 0;
	int errLeft, errRight = 0;

	for (ever)
	{
		//POT_MIN is the value when the fourbar is physically at its lowest location
		errLeft = fourbarTarget - (currLocLeft - POT_FOURBAR_LEFT_MIN) * POT_FOURBAR_LEFT_DIRECTION;
		errRight = fourbarTarget - (currLocRight - POT_FOURBAR_RIGHT_MIN) * POT_FOURBAR_RIGHT_DIRECTION;

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
#define currLoc SensorValue[pot_chainbar]
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
	fourbarTarget = target;
	if (isFourBarLocked)
	{
		stopTask(lockFourBar);
	} else
	{
		isFourBarLocked = true;
	}
	startTask(lockFourBar);
	while (not(approxEq(target, SensorValue[pot_fourbar_left], tolerance) and approxEq(target,
		SensorValue[pot_fourbar_right],
	tolerance)))
	{
		//blocks
	};
	return;
#undef currLoc
}


//----------------END Utility Functions------------

task WheelControls()
{
	for (ever) // a foreverloop
	{
		moveLeftWheels(AxisLeftWheels);
		moveRightWheels(AxisRightWheels);
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
	bool overrideMode = false;
	for (ever)
	{
		if (ButtonChainBarOverrideStart) { overrideMode = true; }
		else if (ButtonChainBarOverrideStop) { overrideMode = false; }

		while (ButtonChainBarUp)
		{
			//overrideMode=false;
			if (isChainBarLocked) releaseChainBar();
			if (SensorValue[pot_chainbar] >= 1200)
				chainBarUp();
		}
		while (ButtonChainBarDown)
		{
			//overrideMode=false;
			if (isChainBarLocked) releaseChainBar();
			chainBarDown();
		}

		/*        while (ButtonChainBarOverrideUp)
		{
		overrideMode = true;
		if (isChainBarLocked) releaseChainBar();
		chainBarUp();
		}

		while (ButtonChainBarOverrideDown)
		{
		overrideMode = true;
		if (isChainBarLocked) releaseChainBar();
		chainBarDown();
		}
		*/
		if (!isChainBarLocked)
		{
			if (not overrideMode)
			{
				if (SensorValue[pot_chainbar] < 1200) chainBarStay();
				else
					chainBarStop();
			} else { chainBarStop(); }

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
		if (ButtonSpecialPickUp)
		{
			holdChainBar(2840);
		}
#ifdef ButtonSpecialDropOffLow
		if (ButtonSpecialDropOffLow)
		{
			holdChainBar(1950);
		}
#endif
#ifdef ButtonSpecialDropOffHigh
		if (ButtonSpecialDropOffHigh)
		{
			holdChainBar(500);
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
			switch (coneCount)
			{
			case 0:
				holdFourBar(50);
				holdChainBar(1225);
				break;
			case 1:
				holdFourBar(50);
				holdChainBar(1310);
				break;
			case 2:
				holdFourBar(100);
				holdChainBar(1210);
				break;
			case 3:
				holdFourBar(230);
				holdChainBar(1210);
				break;
			case 4:
				holdChainBar(2800, 50);
				holdChainBar(1210);
				holdFourBar(300);
				break;
			case 5:
				holdChainBar(2800, 50);
				holdChainBar(1390);
				holdFourBar(425);
				break;
			case 6:
				holdChainBar(2800, 50);
				holdChainBar(1385);
				holdFourBar(515);
				break;
			case 7:
				holdChainBar(2800, 50);
				holdChainBar(1360);
				holdFourBar(600);
				break;
			case 8:
				holdChainBar(2800, 50);
				holdChainBar(1425);
				holdFourBar(700);
				break;
			case 9:
				holdChainBar(2800, 50);
				holdChainBar(1400);
				holdFourBar(900);
				break;
			}
		}
#endif
#endif
#endif

		abortTimeslice();
	}
}


#endif
