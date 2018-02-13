#ifndef autonomousHelpers
#define autonomousHelpers

#include "Driver.h"

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
    const float kp = 0.55; // proportional constant
    const float ki = 0;
    const float kd = 20; // derivatie constant
    int lastErr, allErr, powerOutput = 0;
    int err = 0;

    while (true)
    {
        err = gyroTarget - gyro();
        powerOutput = err * kp + // Proportional
                      allErr * ki + (lastErr - err) * kd;
        lastErr = err;
        allErr += err;
        moveLeftWheels(-powerOutput);
        moveRightWheels(powerOutput);
        abortTimeslice();
    }

}


float wheelsTarget = 0;
bool correctDirection = false;
bool shouldResetGyro = false;

task tMoveWheels()
{ //distance in inches
#define currLocLeft -SensorValue[en_back_left]
#define currLocRight (SensorValue[en_front_right]+SensorValue[en_back_right])/2

    const float distance = wheelsTarget;
    static const float ticksPerInches = 360 / (PI * 4);

    resetEncoders();
    if (correctDirection) { if (shouldResetGyro) resetGyro(); }

    long long sumLeft = 0, sumRight = 0;
    const float kp = 1; // proportional constant
    const float ki = 0;
    const float kd = 20; // derivatie constant
    int lastErrLeft, lastErrRight = 0;
    int powerOutputLeft, powerOutputRight = 0;
    int errLeft, errRight = 0;

    while (true)
    {
        errLeft = distance * ticksPerInches - currLocLeft * EN_FRONT_LEFT_DIRECTION;
        errRight = distance * ticksPerInches - currLocRight * EN_FRONT_RIGHT_DIRECTION;

        powerOutputLeft = errLeft * kp + // Proportional
                          sumLeft * ki + (lastErrLeft - errLeft) * kd;

        powerOutputRight = errRight * kp + // Proportional
                           sumRight * ki + (lastErrRight - errRight) * kd;

        if (correctDirection)
        {
            powerOutputLeft += gyro();
            powerOutputRight -= gyro();
        }

        lastErrLeft = errLeft;
        lastErrRight = errRight;
        sumLeft += errLeft;
        sumRight += errRight;
        moveLeftWheels(powerOutputLeft);
        moveRightWheels(powerOutputRight * 0.95);
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

    while (true)
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
                     tolerance * ticksPerInches))) {}
    //stopTask(tMoveWheels);
    return;

}


#undef currLocLeft
#undef currLocRight

void turn(const int degrees, int tolerance = 10)//positive for turning counter-clockwise
{
    resetGyro();
    if (degrees > 360 or degrees < -360) return; // Cannot throw in robotC
    releaseWheels();

    gyroTarget = -degrees * 10;
    startTask(tTurn);

    while (not approxEq(gyro(), -degrees * 10, tolerance)) {}

}

void mobileGoal(const int target, bool block = false, int tolerance = 20)
{
    stopTask(tMoveMobileGoal);
    mobileGoalTarget = target;
    startTask(tMoveMobileGoal);
    if (block)
    {
        while (not approxEq(target, SensorValue[pot_mb], tolerance)) {}

    }

}


#endif
