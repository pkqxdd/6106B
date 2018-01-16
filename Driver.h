#ifndef drivers
#define drivers

// -----------------BEGIN Global Constants Configuration-------------------
const int MB_POWER = 60; // power to mobile goal lift
const int FOURBAR_POWER = 100; //power to fourbar
const int CHAINBAR_POWER = 80; // power to chainbar
const int ROLLER_POWER = 127; // power to chainbar
const int FOURBAR_ANTIGRAVITY = 10; //power to fourbar when it is in the "stop" position
const int MB_ANTIGRAVITY = 0; //power to mobile goal lift when it is in the "stop" position
const int CHAINBAR_ANTIGRAVITY = 20;
const int ROLLER_ANTIGRAVITY = 8;

const int POT_CHAINBAR_MIN = 1052;
const int POT_CHAINBAR_MAX = 3190;

//POT_MIN is the value when the fourbar is physically at its lowest location. MIN may be larger than MAX in value.
const int POT_FOURBAR_LEFT_DIRECTION = -1;
const int POT_FOURBAR_LEFT_MAX = 1700;
const int POT_FOURBAR_LEFT_MIN = 3140;

const int POT_FOURBAR_RIGHT_DIRECTION = 1;
const int POT_FOURBAR_RIGHT_MAX = 3800;
const int POT_FOURBAR_RIGHT_MIN = 2325;

const int RIGHT_MB_START = 0; //I2C 6
const int RIGHT_MB_TRAVEL = 375;
const int RIGHT_MB_MAX = 1220;

const int LEFT_MB_START = 0; //I2C 5
const int LEFT_MB_TRAVEL = -375;
const int LEFT_MB_MAX = -1220;

const int FRONT_LEFT_DIRECTION = 1;
const int FRONT_RIGHT_DIRECTION = 1;
const int BACK_LEFT_DIRECTION = 1;
const int BACK_RIGHT_DIRECTION = 1;

// ------------------END Global Constants Configuration----------------------
// -----------------BEGIN Keymap Configuration------------------

//#include "KeymapSinglePlayer.h"
#include "KeymapTwoPlayer.h"

// -----------------END Keymap Configuration----------------
// ------------------BEGIN Utility Functons---------------

#define min(a, b) ((a)<(b)?(a):(b))
#define max(a, b) ((a)>(b)?(a):(b))


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
    motor[mb_left] = MB_POWER + 50;
    motor[mb_right] = MB_POWER + 50;
}


void mobileGoalDown()
{
    motor[mb_left] = -MB_POWER;
    motor[mb_right] = -MB_POWER;
}

void mobileGoalStop()
{
    motor[mb_left] = 0;
    motor[mb_right] = 0;
}

void fourBarLeftUp()
{
    motor[fb_left] = FOURBAR_POWER + FOURBAR_ANTIGRAVITY;
}

void fourBarRightUp()
{
    motor[fb_right] = FOURBAR_POWER + FOURBAR_ANTIGRAVITY -
                      4.25;//+.25*(SensorValue[pot_fourbar_left]-SensorValue[pot_fourbar_right]-17);
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
    clearTimer(T1);
    while (time1(T1) < 2500) motor[roller] = -ROLLER_POWER;
    return;
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
    motor[chainbar] = CHAINBAR_POWER + CHAINBAR_ANTIGRAVITY;
}

void chainBarMove(const int power)
{
    motor[chainbar] = power;
}

void chainBarDown()
{
    motor[chainbar] = -CHAINBAR_POWER + CHAINBAR_ANTIGRAVITY;
}

void chainBarStop()
{
    motor[chainbar] = CHAINBAR_ANTIGRAVITY;
}


int chainbarTarget = 0;
int fourbarTarget = 0;
bool isFourBarLocked = false;
bool isChainBarLocked = false;

task lockChainbar()
{ // hold the chainbar in place. Call stoptask to release it
#define currLoc SensorValue[pot_chainbar]
    const float kp = -0.25; // proportional constant
    const float kd = -0.5; // derivatie constant
    int lastErr, powerOutput = 0;
    int err = 0;

    while (true)
    {
        err = chainbarTarget - currLoc;
        powerOutput = CHAINBAR_ANTIGRAVITY + //Base power
                      err * kp + // Proportional
                      (lastErr - err) * kd;
        lastErr = err;
        chainBarMove(powerOutput);
        abortTimeSlice();
    }
#undef currLoc
}


task lockFourBar()
{ // hold the fourbar in place. Call stoptask to release it

#define currLocLeft SensorValue[pot_fourbar_left]
#define currLocRight SensorValue[pot_fourbar_right]
    const float kp = 0.25; // proportional constant
    const float kd = 0.5; // derivatie constant
    int lastErrLeft, lastErrRight = 0;
    int powerOutputLeft, powerOutputRight = 0;
    int errLeft, errRight = 0;

    while (true)
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
        abortTimeSlice();
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

void holdChainBar(int target, const bool block=false, const int tolerance=50)
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

void holdFourBar(const int target, const bool block=false, const int tolerance=50)
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

void resetMobileGoalEncoder(const float t)
{// t is the time to move up
    motor[mb_left] = MB_POWER;
    motor[mb_right] = MB_POWER;
    nMotorEncoder[mb_left] = 0;
    nMotorEncoder[mb_right] = 0;

    clearTimer(T2);
    while (time1(T2) < t)
    {
        mobileGoalUp();
    }

    motor[mb_left] = 0;
    motor[mb_right] = 0;

    nMotorEncoder[mb_left] = 0;
    nMotorEncoder[mb_right] = 0;

}

//----------------END Utility Functions------------

task WheelControls()
{
    while (true) // a foreverloop
    {
        moveLeftWheels(AxisLeftWheels);
        moveRightWheels(AxisRightWheels);
    abortTimeSlice();

        }
}

task FourBarControls()
{
    while (true)
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
    abortTimeSlice();
        }
}

task RollerControls()
{
    bool shouldStop = true;
    while (true)
    {
        if (ButtonRollerIn)
        {
            rollerIn();
            shouldStop = false;
        } else if (ButtonRollerOut)
        {
            rollerOut();
            shouldStop = true;
        } else
        {
            if (shouldStop) rollerZero();
            else rollerStop();
        }
    abortTimeSlice();
        }
}

task ChainBarControls()
{
    while (true)
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
        if (!isChainBarLocked) chainBarStop();
    abortTimeSlice();
        }
}

int coneCount = 0;

task SpecialControls()
{
    bool wasPressedIncrement = false;
    bool wasPressedDecrement = false;
    while (true)
    {
        if (ButtonSpecialPickUp)
        {
            if (SensorValue[pot_fourbar_right] < 2555)
            {
                holdChainBar(1450);
            } else
            {
                holdChainBar(1200);
            }
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
            holdChainBar(440);
        }
        if (vexRT[Btn8L])
        {
            //holdFourBar(600);
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
#ifdef ButtonSpecialDropOff
        if (ButtonSpecialDropOff)
        {
            switch (coneCount)
            {
                case 0:
                		holdFourBar(675);
                    holdChainBar(1950);
                    break;
                case 1:
                    holdFourBar(50);
                    holdChainBar(496);
                    break;
                case 2:
                    holdFourBar(50);
                    holdChainBar(360);
                    break;
                case 3:
                		holdFourBar(200);
                    holdChainBar(525);
                    break;
                case 4:
                    holdChainBar(324);
                    holdFourBar(335);
                    break;
                case 5:
                    holdChainBar(330);
                    holdFourBar(400);
                    break;
                case 6:
                    holdChainBar(353);
                    holdFourBar(420);
                    break;
                case 7:
                    holdChainBar(403);
                    holdFourBar(475);
                    break;
                case 8:
                    holdChainBar(592);
                    holdFourBar(558);
                    break;
                case 9:
                    holdChainBar(619);
                    holdFourBar(666);
                    break;/*
				case 10:
				holdChainBar();
				holdFourBar();
				break;*/
            }
        }
#endif
#endif
#endif
abortTimeSlice();
    }
}

int mb_level = 3;
int target = 0;
int leftEncoder, rightEncoder, powerOutputLeft, powerOutputRight = 0;
int errLeft, errRight = 0;


task SmoothMobileGoalLift()
{
#define left  (nMotorEncoder[mb_left]) //assuming left side has the negative reading
#define right (nMotorEncoder[mb_right])

    bool wasPressed = false;
    const float kp = -0.75; // proportional constant
    //const float kd=-.25; // derivatie constant
    int mapLevelToTarget[4] = {-1300, -675, -300, 20};

    while (true)
    {
        if (ButtonMobileGoalUp)
        { //so the target don't get shoot into some absurd valule
            if (!wasPressed)
            {
                wasPressed = true;
                if (mb_level < 3) mb_level += 1;
                else resetMobileGoalEncoder(200);
            }
        } else if (ButtonMobileGoalDown)
        {
            if (!wasPressed)
            {
                wasPressed = true;
                if (mb_level > 0) mb_level -= 1;
            }
        } else
        {
            wasPressed = false;
        }

        target = mapLevelToTarget[mb_level];

        leftEncoder = left;
        rightEncoder = right;
        errLeft = left - target;
        errRight = right - target;
        powerOutputLeft = errLeft * kp;
        powerOutputRight = errRight * kp;
        motor[mb_left] = powerOutputLeft;
        motor[mb_right] = powerOutputRight; //smoothing both sides to make them balance
abortTimeSlice();
       }
}



#undef right
#undef left
#endif
