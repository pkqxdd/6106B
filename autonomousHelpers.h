#ifndef autonomousHelpers
#define autonomousHelpers
#include "Driver.h"

<<<<<<< HEAD
void ClearEncoders()
{
nMotorEncoder[front_left]=0;
nMotorEncoder[front_right]=0;
nMotorEncoder[back_left]=0;
nMotorEncoder[back_right]=0;
}

void TurnCW(int degrees)
{
	moveLeftWheels(/*turn constant*/500 * degrees/360);
	moveRightWheels(-);
}
=======
void MoveAllWheelsStraight(const int power){
#define fl nMotorEncoder[front_left]*FRONT_LEFT_DIRECTION
#define bl nMotorEncoder[back_left]*BACK_LEFT_DIRECTION
#define fr nMotorEncoder[front_right]*FRONT_RIGHT_DIRECTION
#define br nMotorEncoder[back_right]*BACK_RIGHT_DIRECTION 
>>>>>>> 7d7b12eba5fc3c1fb2bdb6316d635617113a4802

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


<<<<<<< HEAD
if (currLoc<target)
{
while (currLoc<target)
{ //if average of four wheels...
=======
if (currLoc<target){
while (currLoc<target){ // go forward
>>>>>>> 7d7b12eba5fc3c1fb2bdb6316d635617113a4802

	MoveAllWheelsStraight(80);
	// moveLeftWheels(100);
	// moveRightWheels(95);

}
}
<<<<<<< HEAD
else
 {
	while (currLoc>target)
	{ //if average of four wheels...
=======
else {
	while (currLoc>target){ //go backward
>>>>>>> 7d7b12eba5fc3c1fb2bdb6316d635617113a4802

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
