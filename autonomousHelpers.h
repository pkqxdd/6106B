#ifndef autonomousHelpers
#define autonomousHelpers
#include "Driver.h"



void resetEncoders(){
SensorValue[en_front_left]=0;
SensorValue[en_front_right]=0;
}



float wheelsTarget=0;



task tMoveWheels(){ //distance in inches
#define currLocLeft SensorValue[en_front_left]
#define currLocRight SensorValue[en_front_right]

const float distance=wheelsTarget;
static const float ticksPerInches=360/(PI*4);
resetEncoders();


    const float kp = 3; // proportional constant
    const float kd = 3; // derivatie constant
    int lastErrLeft, lastErrRight = 0;
    int powerOutputLeft, powerOutputRight = 0;
    int errLeft, errRight = 0;

    while (true)
    {
        errLeft = distance*ticksPerInches-currLocLeft*EN_FRONT_LEFT_DIRECTION;
        errRight = distance*ticksPerInches-currLocRight*EN_FRONT_RIGHT_DIRECTION;

        powerOutputLeft =
                          errLeft * kp + // Proportional
                          (lastErrLeft - errLeft) * kd;

        powerOutputRight =
                           errRight * kp + // Proportional
                           (lastErrRight - errRight) * kd;

        lastErrLeft = errLeft;
        lastErrRight = errRight;
        moveLeftWheels(powerOutputLeft);
        moveRightWheels(powerOutputRight);
    }


}

void moveWheels(const float distance,const float tolerance=10){
static const float ticksPerInches=360/(PI*4);


wheelsTarget=distance;
stopTask(tMoveWheels);
startTask(tMoveWheels);
while (not (approxEq(currLocLeft*EN_FRONT_LEFT_DIRECTION,distance*ticksPerInches,tolerance) and
    						approxEq(currLocRight*EN_FRONT_RIGHT_DIRECTION,distance*ticksPerInches,tolerance) ))

    						{}
    						return;

}


#undef currLocLeft
#undef currLocRight

void turn(const int degrees)//positive for turning clockwise
{
stopTask(tMoveWheels);


}


#endif
