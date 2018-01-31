#ifndef autonomousHelpers
#define autonomousHelpers
#include "Driver.h"


void turnDegrees(const int degrees)
{

}


void moveAllWheelsStraight(const int power){
#define fl nMotorEncoder[front_left]*FRONT_LEFT_DIRECTION
#define bl nMotorEncoder[back_left]*BACK_LEFT_DIRECTION
#define fr nMotorEncoder[front_right]*FRONT_RIGHT_DIRECTION
#define br nMotorEncoder[back_right]*BACK_RIGHT_DIRECTION

#define scaleFactor 0.25

int diffFront= scaleFactor * (fr-fl);
int diffBack = scaleFactor * (br-bl);

motor[front_left]	= power - diffBack;
motor[front_right]	= power + diffBack;
motor[back_left]  	= power - diffBack;
motor[back_right] 	= power + diffBack;

#undef front_left
#undef back_left
#undef front_right
#undef back_right
#undef scaleFactor
}

void absoluteMoveAllWheelsTo(const int target){
//#define currLoc (abs(nMotorEncoder(front_left))+abs(nMotorEncoder(back_left))+abs(nMotorEncoder(front_right))+abs(nMotorEncoder(back_right)))/4
#define currLoc (\
	nMotorEncoder[front_left]*FRONT_LEFT_DIRECTION + \
	nMotorEncoder[front_right]*FRONT_RIGHT_DIRECTION + \
	nMotorEncoder[back_left]*BACK_LEFT_DIRECTION + \
	nMotorEncoder[back_right]*BACK_RIGHT_DIRECTION ) / 4 //average






moveLeftWheels(0); //stop
moveRightWheels(0);
return;
#undef currLoc
}



void moveToMobileGoalLevel(const int level)
{
}

void resetEncoders(){
SensorValue[en_front_left]=0;
SensorValue[en_front_right]=0;
}

#endif
