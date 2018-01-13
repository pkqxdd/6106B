#ifndef autonomousHelpers
#define autonomousHelpers
#include "Driver.h"


void AbsoluteMoveAllWheelsTo(int target){
#define currLoc (abs(nMotorEncoder(front_left))+abs(nMotorEncoder(back_left))+abs(nMotorEncoder(front_right))+abs(nMotorEncoder(back_right)))/4


int dis[4]={0,0,0,0}; //record for the distance of wheels

if (currLoc<target){
while (currLoc<target){ //if average of four wheels...

	dis[0]=nMotorEncoder(front_left);
	dis[1]=nMotorEncoder(front_right);
	dis[2]=nMotorEncoder(back_left);
	dis[3]=nMotorEncoder(back_right);
	moveLeftWheels(100);
	moveRightWheels(95);

}
}
else {
	while (currLoc>target){ //if average of four wheels...

	dis[0]=nMotorEncoder[front_left];
	dis[1]=nMotorEncoder[front_right];
	dis[2]=nMotorEncoder[back_left];
	dis[3]=nMotorEncoder[back_right];
	moveLeftWheels(-100);
	moveRightWheels(-95);
}
}
moveLeftWheels(0);
moveRightWheels(0);

}
#undef currLoc


void moveToMobileGoalLevel(const int level){

mb_level=level;
}


#endif
