#ifndef autonomousHelpers
#define autonomousHelpers
#include "Driver.h"


void ClearEncoders()
{
nMotorEncoder[front_left]=0;
nMotorEncoder[front_right]=0;
nMotorEncoder[back_left]=0;
nMotorEncoder[back_right]=0;
}

/*
void TurnCW(int degrees)
{
	moveLeftWheels(500 * degrees/360);
	moveRightWheels(-);
}
*/

void MoveAllWheelsStraight(const int power){
#define fl nMotorEncoder[front_left]*FRONT_LEFT_DIRECTION
#define bl nMotorEncoder[back_left]*BACK_LEFT_DIRECTION
#define fr nMotorEncoder[front_right]*FRONT_RIGHT_DIRECTION
#define br nMotorEncoder[back_right]*BACK_RIGHT_DIRECTION

#define scaleFactor 0.5

int diffFront= scaleFactor * (fr-fl);
int diffBack = scaleFactor * (br-bl);

motor[front_left]	= power - diffFront;
motor[front_right]	= power + diffFront;
motor[back_left]  	= power - diffBack;
motor[back_right] 	= power + diffBack;

#undef front_left
#undef back_left
#undef front_right
#undef back_right
}

void AbsoluteMoveAllWheelsTo(int target){
//#define currLoc (abs(nMotorEncoder(front_left))+abs(nMotorEncoder(back_left))+abs(nMotorEncoder(front_right))+abs(nMotorEncoder(back_right)))/4
#define currLoc (\
	nMotorEncoder[front_left]*FRONT_LEFT_DIRECTION + \
	nMotorEncoder[front_right]*FRONT_RIGHT_DIRECTION + \
	nMotorEncoder[back_left]*BACK_LEFT_DIRECTION + \
	nMotorEncoder[back_right]*BACK_RIGHT_DIRECTION ) / 4 //average



if (currLoc<target){
while (currLoc<target){ // go forward

	MoveAllWheelsStraight(80);
	// moveLeftWheels(100);
	// moveRightWheels(95);
}
}

else {
	while (currLoc>target){ //go backward

	MoveAllWheelsStraight(-80);
	// moveLeftWheels(-100);
	// moveRightWheels(-95);
}
}

moveLeftWheels(0); //stop
moveRightWheels(0);
#undef currLoc
}



void moveToMobileGoalLevel(const int level)
{
mb_level=level;
}

void resetEncoders(){
nMotorEncoder[front_left]=0;
nMotorEncoder[front_right]=0;
nMotorEncoder[back_left]=0;
nMotorEncoder[back_right]=0;
}


#endif
