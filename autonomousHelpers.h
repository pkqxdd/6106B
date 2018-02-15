#ifndef autonomousHelpers
#define autonomousHelpers

#include "Driver.h"
#define DEBUG
void resetEncoders()
{
    SensorValue[en_front_left] = 0;
    SensorValue[en_front_right] = 0;
    SensorValue[en_back_left] = 0;
    SensorValue[en_back_right] = 0;
}

int gyroTarget = 0;

int gyro()
{

    return (SensorValue[gyro_left] + SensorValue[gyro_right]) / 2;

}

void resetGyro()
{
    SensorValue[gyro_left] = 0;
    SensorValue[gyro_right] = 0;
}


task tTurn()
{
    const float kp = 0.3; // proportional constant
    const float ki = 0;
    const float kd = 20; // derivatie constant
    static int lastMeasure=nSysTime;
    int lastErr, allErr, powerOutput = 0;
    int err = 0;
    for(ever)
    {
    		wait1Msec(1);
    		int dt=lastMeasure-nSysTime;
        err = gyroTarget - gyro();
        powerOutput = err * kp + // Proportional
         allErr * ki + (lastErr - err)/dt * kd;
        lastErr = err;
        allErr += err;
        moveLeftWheels(-powerOutput);
        moveRightWheels(powerOutput);

        #ifdef DEBUG
                //formatted as Error P I D dt
        writeDebugStreamLine("Turn at %d", nSysTime);
        writeDebugStreamLine("Data: %d | %d | %d | %d | %d |",err, err*kp, 0, (lastErr - err)/dt * kd, dt);
        writeDebugStreamLine("Gyro: %d",gyro());
        writeDebugStreamLine("Output: %d", powerOutput);
        writeDebugStreamLine("--------------------");
#endif
        lastMeasure=nSysTime;
                abortTimeslice();
    }

}


float wheelsTarget = 0;
bool correctDirection = false;
bool shouldResetGyro = false;


task tMoveWheels()
{ //distance in inches
#define currLocLeft (SensorValue[en_front_right]-SensorValue[en_back_left])/2
#define currLocRight (SensorValue[en_front_right]+SensorValue[en_back_right])/2
		int lastMeasure=nSysTime;
    const float distance = wheelsTarget;
    static const float ticksPerInches = 360 / (PI * 4);
		int dt=nSysTime-lastMeasure;
    resetEncoders();
    if (correctDirection) { if (shouldResetGyro) resetGyro(); }

    long long sumLeft = 0, sumRight = 0;
    float kp = 1; // proportional constant
    const float ki = 0.00001;
    const float kd = 80; // derivatie constant
    int lastErrLeft, lastErrRight = 0;
    int powerOutputLeft, powerOutputRight = 0;
    int errLeft, errRight = 0;

    for(ever)
    {
    		wait1Msec(1);
    		kp=0.85-(nImmediateBatteryLevel/1000-7)/4;
        errLeft = distance * ticksPerInches - currLocLeft * EN_FRONT_LEFT_DIRECTION;
        errRight = distance * ticksPerInches - currLocRight * EN_FRONT_RIGHT_DIRECTION;
				sumLeft += errLeft*dt;
        sumRight += errRight*dt;
        dt=nSysTime-lastMeasure;

        powerOutputLeft = errLeft * kp + // Proportional
                          (sumLeft+errLeft*dt) * ki + // Integral
                          (lastErrLeft - errLeft)/dt * kd;

        powerOutputRight = errRight * kp + // Proportional
                           sumRight * ki + // Integral
                           (lastErrRight - errRight)/dt * kd;

        if (correctDirection)
        {
            powerOutputLeft += gyro();
            powerOutputRight -= gyro();
        }

        //formatted as Error P I D dt
#ifdef DEBUG
        writeDebugStreamLine("Wheels at %d", nSysTime);
        writeDebugStreamLine("Left: %d | %d | %d | %d | %d |",errLeft, errLeft*kp, sumLeft*ki, (lastErrLeft - errLeft)/dt * kd, dt);
        writeDebugStreamLine("Right: %d | %d | %d | %d | %d |",errRight, errRight*kp, sumRight*ki, (lastErrRight - errRight)/dt * kd, dt);
        writeDebugStreamLine("Gyro: %d",gyro());
        writeDebugStreamLine("Output: L: %d | R: %d",powerOutputLeft,powerOutputRight);
        writeDebugStreamLine("--------------------");
#endif

        lastErrLeft = errLeft;
        lastErrRight = errRight;
        moveLeftWheels(powerOutputLeft);
        moveRightWheels(powerOutputRight * 0.95);
        lastMeasure=nSysTime;
        abortTimeslice();
    }

}

int mobileGoalTarget = 0;

task tMoveMobileGoal()
{
    const float kp = -1; // proportional constant
    const float ki = 0;
    const float kd = 5; // derivatie constant
    int lastErr, allErr, powerOutput = 0;
    int err = 0;

    for(ever)
    {
        err = mobileGoalTarget - SensorValue[pot_mb];
        powerOutput = err * kp + // Proportional
                      allErr * ki + (lastErr - err) * kd;
        lastErr = err;
        allErr += err;
        moveMobileGoal(powerOutput);
        abortTimeslice();
    }

}


void releaseWheels()
{
    stopTask(tTurn);
    stopTask(tMoveWheels);
}


void moveWheels(const float distance, const bool straight = false, const float tolerance = 0.5,
                const bool shouldResetGyroscope = true)
{
    static const float ticksPerInches = 360 / (PI * 4);

    correctDirection = straight;
    shouldResetGyro = shouldResetGyroscope;
    wheelsTarget = distance;
    releaseWheels();
    startTask(tMoveWheels);


    while (not(
            approxEq(currLocLeft * EN_FRONT_LEFT_DIRECTION, distance * ticksPerInches, tolerance * ticksPerInches) and
            approxEq(currLocRight * EN_FRONT_RIGHT_DIRECTION, distance * ticksPerInches,
                     tolerance * ticksPerInches))) {} //blocks when target not reached
    return;
#ifdef DEBUG
for (int ii=0;ii<10;ii++){
writeDebugStreamLine("!!!!!!!!Target %d reached at %d.", wheelsTarget,nSysTime);
writeDebugStreamLine("!!!!!!!!Current reading: L: %d | R: %d",currLocLeft * EN_FRONT_LEFT_DIRECTION, currLocRight * EN_FRONT_RIGHT_DIRECTION);
}
#endif

}


#undef currLocLeft
#undef currLocRight

void turn(const int degrees, int tolerance = 10) //positive number for turning clockwise
{
    resetGyro();
    if (degrees > 360 or degrees < -360) return; // Cannot throw an exception in robotC. Just return
    releaseWheels();

    gyroTarget = -degrees * 10;
    startTask(tTurn);

    while (not approxEq(gyro(), -degrees * 10, tolerance)) {} //blocks when target not reached
#ifdef DEBUG
for (int ii=0;ii<10;ii++)
writeDebugStreamLine("!!!!!Target %d reached at %d. Current reading: %d ", gyroTarget,nSysTime,gyro());
#endif
}

void mobileGoal(const int target, bool block = false, int tolerance = 20)
{
    stopTask(tMoveMobileGoal);
    mobileGoalTarget = target;
    startTask(tMoveMobileGoal);
    if (block)
    {
        while (not approxEq(target, SensorValue[pot_mb], tolerance)) {} //blocks when target not reached

    }

}


#endif
